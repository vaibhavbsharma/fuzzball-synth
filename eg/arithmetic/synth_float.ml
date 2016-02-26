(* usage: synth.ml <bin> <# outer args> <# inner args> <rand. seed>
   Note that the FUZZBALL_LOC and Z3_LOC/MATHSAT_LOC enviroment variables 
   need to be set *)

open Printf
#load "str.cma"  (* used for regular expressions *)
#load "unix.cma" (* used to execute system commands *)


(*** Read command line args ***)

(* 'outer function' = the 'black box' function (f1)
   'inner function' = the function whose arguments we want to adapt (f2) *)
let print_usage () = 
  (printf "usage: synth.ml <bin> <# outer args> <# inner args> <rand. seed>\n%!";
   exit 1)
let bin = 
  try Sys.argv.(1)
  with Invalid_argument _ -> print_usage ()
let outer_nargs = 
  try int_of_string Sys.argv.(2)
  with Invalid_argument _ -> print_usage ()
let inner_nargs =
  try int_of_string Sys.argv.(3)
  with Invalid_argument _ -> print_usage ()
let _ = 
  try Random.init (int_of_string Sys.argv.(4))
  with Invalid_argument _ -> print_usage ()


(*** current adaptor and test set ***)

(* default adaptor has all values set to 0 *)
let create_adapt num_args =
  let tree_depth = 2 in (* hardcoded for now *)
  let rec create_tree d base var_name = 
    if d > 0
    then ["-extra-condition " ^ (var_name ^ "_type_" ^ base) ^ ":reg8_t==0:reg8_t";
          "-extra-condition " ^ (var_name ^ "_val_" ^ base) ^ ":reg64_t==0:reg64_t"]
         @ (create_tree (d-1) (base ^ "0") var_name)
         @ (create_tree (d-1) (base ^ "1") var_name)
    else [] in
  let rec main_loop n =
    if n = 0 then []
    else let x = String.make 1 (Char.chr ((Char.code 'a') + (n-1))) in 
           (create_tree tree_depth "R" x) @ (main_loop (n-1))
  in main_loop num_args
let adapt = ref (create_adapt inner_nargs)

let tests = ref [] (* will be a list of lists *)


(*** utility functions ***)

(* print_tests : () -> () 
   print out the current set of tests *)
let print_tests () = 
  List.iter 
    (fun test -> List.iter (fun el -> printf "%Lx %!" el) test; printf "\n%!") 
    !tests
  
(* print_adaptor : () -> ()
   print out the current adaptor in a readable format *)
let print_adaptor () =
  List.iter (fun el -> let l = Str.split (Str.regexp " \\|:\\|=") el in
                       printf "%s = %s%!\n" (List.nth l 1) (List.nth l 4))
            !adapt

(* match_regex : string -> string -> bool 
   check that a string matches the provided regex *)
let match_regex str regex =
  Str.string_match (Str.regexp regex) str 0

(* syscall : string -> string list
   return the standard out of cmd as a list of lines *)
let syscall cmd = 
  (*let _ = printf "Command: %s\n%!" cmd in*)
  let ic = Unix.open_process_in cmd in
  let lines = ref [] in
  (try
     while true do
       lines := input_line ic :: !lines
     done
   with End_of_file -> ());
  let _ = Unix.close_process_in ic in
  List.rev !lines


(*** FUZZBall command line arguments ***)

(* a hardcoded path for the fevis repository *)
let fuzzball = "../../../../tools/fuzzball/exec_utils/fuzzball"

(* Z3 or MathSAT are required for floating point operations *)
let solver =
  try Sys.getenv "SOLVER" 
  with Not_found -> 
    failwith "Set the location of the solver with 'export SOLVER=...'"

let main_addr = 
  match syscall ("nm " ^ bin ^ " | fgrep ' T main'") with
  | [str] -> "0x" ^ String.sub str 0 16
  | _ -> failwith "Unexpected main address format"

let symbolic_input =
  (* note: this assumes that the values we want to make symbolic have single
           character variable names; not great error handling here... *)
  let rec loop l n =
    if n = outer_nargs
    then []
    else let x = String.make 1 (Char.chr ((Char.code 'a') + n)) in
         ("-symbolic-long 0x0" ^ (String.sub (List.hd l) 0 16) ^ "=" ^ x) 
           :: (loop (List.tl l) (n+1))
  in loop (syscall ("nm " ^ bin ^ " | grep ' B [a-z]$'")) 0

(* commented out because -skip-call-ret-symbol is being uncooperative
let symbolic_input =
  let rec loop l n =
    match l with
    | [] -> (if n <> outer_nargs 
             then printf "\nUnexpected number of strtoul calls; something may have gone wrong\n\n%!" 
             else ()); []
    | (h::t) -> let x = String.make 1 (Char.chr ((Char.code 'a') + n)) in
                ("-skip-call-ret-symbol-once 0x0" ^ (String.sub h 2 6) ^ "=" ^ x)
                :: (loop t (n+1))
  in loop (syscall ("objdump -dr " ^ bin ^ " | grep 'call.*strtoul'")) 0
*)
let outer_call_addr =
  match syscall ("objdump -dr " ^ bin ^ " | grep 'call.*f1'") with
  | [str1; str2] -> "0x0" ^ String.sub str2 2 6
  | _ -> failwith "Unexpected function call address formats"

let inner_func_addr = 
  match syscall ("nm " ^ bin ^ " | fgrep ' T f2'") with
  | [str] -> "0x" ^ String.sub str 0 16
  | _ -> failwith "Unexpected inner function format"

(*let match_jne_addr =
  match syscall ("objdump -dr " ^ bin ^ " | grep 'jne.*compare+'") with
  | [str] -> "0x" ^ String.sub str 2 6
  | _ -> failwith "Unexpected jne address format"*)

let solver_opts = ["-solver smtlib-batch"; "-solver-path"; solver]

let fields = 
  let tree_depth = 2 in (* hardcoded for now *)
  let rec create_tree d base var_name =
    if d > 0
    then [(var_name ^ "_type_" ^ base, 8);
          (var_name ^ "_val_" ^ base, 64)]
         @ (create_tree (d-1) (base ^ "0") var_name)
         @ (create_tree (d-1) (base ^ "1") var_name)
    else [] in
  let rec create_fields n =
    if n = 0 then []
    else let x = String.make 1 (Char.chr ((Char.code 'a') + (n-1))) in
         (create_tree tree_depth "R" x) @ (create_fields (n-1)) in
  create_fields inner_nargs
 

(*** check_adaptor : () -> (bool * (int * int))
     given the specification of an adaptor, execute it with symbolic
     inputs to either check it, or produce a counterexample ***)
let check_adaptor () = 
  let cmd = [fuzzball; "-linux-syscalls"; bin]
            @ solver_opts @ ["-arch";"x64"]
            @ ["-fuzz-start-addr"; main_addr]
            @ symbolic_input
            @ [(*"-branch-preference"; match_jne_addr ^ ":0";*)
               "-trace-iterations"; "-trace-assigns"; "-solve-final-pc";
               "-synthesize-adaptor"; 
               "arithmetic_float:" ^
               outer_call_addr ^ ":" ^ (string_of_int outer_nargs) ^ ":" ^
               inner_func_addr ^ ":" ^ (string_of_int inner_nargs)]
            @ !adapt (* representation of the adaptor as '-extra-condition' arguments *)
            @ ["-zero-memory";
               "-random-seed"; string_of_int (Random.int 10000000); 
               "--"; bin] in
  let _ = printf "%s\n%!" (String.concat " " cmd) in
  let ic = Unix.open_process_in (String.concat " " cmd) in
  let ce = ref (Array.make outer_nargs 0L) in
  (* read_results : string list -> (int * int) -> bool -> (bool * (int * int))
     read through the results of the call to FuzzBALL keeping track of
     the number of matches and mismatches, and record a counterexample
     for the first mismatch *)
  let rec read_results (matches, fails) record_ce = 
    try
      let line = input_line ic in
      let _ = printf " %s\n%!" line in
      match line with
      | "Match" -> read_results (matches + 1, fails) record_ce
      | "Mismatch" -> read_results (matches, fails + 1) true
      | _ when (match_regex line "^Input vars: .*$") && record_ce ->
          (* use regular expressions to pull out values for a, b and c;
             if no values for x and y are specified, assume that they are 0 *)
          List.iter 
            (fun v ->
               if (match_regex v "^.=0x[0-9a-f]+$")
               then let idx = (Char.code (String.get v 0)) - (Char.code 'a') in
                    let value = Int64.of_string 
                                  (String.sub v 2 ((String.length v) - 2)) in
                    Array.set !ce idx value
               else ())
            (Str.split (Str.regexp " ") line);
            (* after updating ce once, we are done *)
            let _ = Unix.close_process_in ic in
            (false, Array.to_list !ce)
      | _ -> read_results (matches, fails) record_ce
    with End_of_file -> 
      let _ = Unix.close_process_in ic in
      if matches = 0 && fails = 0 
      then failwith "Missing results from check run"
      else (true, Array.to_list !ce) in
  read_results (0, 0) false


(*** try_synth : () -> string
     given a set of tests, run with the adaptor symbolic to see if we can
     synthesize an adaptor that works for those tests ***)
let try_synth () = 
  let test_str = String.concat "\n"  
                   (List.map 
                     (fun test -> String.concat " " 
                                    (List.map (fun el -> sprintf "%Lx" el) test)) 
                     !tests) in
  let testc = open_out "tests" in
  let _ = output_string testc test_str in
  let _ = close_out testc in
  let cmd = [fuzzball; "-linux-syscalls"; bin] 
            @ solver_opts  @ ["-arch"; "x64"]
            @ ["-fuzz-start-addr"; main_addr]
            @ ["-trace-iterations"; "-trace-assigns"; "-solve-final-pc";
               "-synthesize-adaptor"; 
               "arithmetic_float:" ^
               outer_call_addr ^ ":" ^ (string_of_int outer_nargs) ^ ":" ^ 
               inner_func_addr ^ ":" ^ (string_of_int inner_nargs); 
               (*"-branch-preference"; match_jne_addr ^ ":1";*)
               "-zero-memory";
               "-random-seed"; string_of_int (Random.int 10000000);
               "--"; bin; "-f tests"] in
  let _ = printf "%s\n%!" (String.concat " " cmd) in
  let ic = Unix.open_process_in (String.concat " " cmd) in
  (* read_results : string list -> bool -> string
     read through the results of the call to FuzzBALL looking for a case
     where all test are successfully passed *)
  let rec read_results success = 
    try
      let line = input_line ic in
      let _ = if not (match_regex line "^Input vars: .*$")
              then printf " %s\n%!" line 
              else () in
      match line with 
      | "All tests succeeded!" -> read_results true
      | _ when (match_regex line "^Input vars: .*$") && success ->
          (* use regular expressions to pull out values for the adaptor fields
             and return the adaptor *)
          let specified_vals = ref [] in
          printf "  %s\n%!" line;
          List.iter 
            (fun v ->
               if (match_regex v "^.*=0x[0-9a-f]+$")
               then match Str.split (Str.regexp "=") v with
                    | name::value::[] -> 
                        specified_vals := (name, Int64.of_string value) :: !specified_vals
                    | _ -> failwith "Parse failure on variable assignment"
               else if (match_regex v "^Input$\\|^vars:$") 
                    then () 
                    else failwith "Parse failure on variable assignment")
            (Str.split (Str.regexp " ") line);
          let rec getval l k = 
            match l with [] -> None 
                       | (k',v)::t -> if k = k' then Some v else getval t k in
          let new_adaptor = ref [] in
          List.iter 
            (fun (name, size) -> 
               let v = match getval !specified_vals name with 
                       | None -> 0L | Some v -> v in
               new_adaptor := !new_adaptor @
                 [sprintf "-extra-condition %s:reg%d_t==0x%Lx:reg%d_t"
                    name size v size])
            fields;
          (* after finding a suitable adaptor, we are done *)
          let _ = Unix.close_process_in ic in
          !new_adaptor
      | _ -> read_results success
    with End_of_file -> 
      let _ = Unix.close_process_in ic in
      if not success
      then (printf "Synthesis failure: seems the functions are not equivalent.\n%!";
            exit 2)
      else [] in
  read_results false


(*** main : () -> ()
     start with a simple adaptor and no tests and alternate between test 
     generation and synthesis, updating the adaptor and test set as needed ***)
let rec main () =
  match check_adaptor () with
  | (true, _) -> (* we found a suitable adaptor *)
      printf "Success!\nFinal test set:\n%!";
      print_tests ();
      printf "Final adaptor:\n%!";
      print_adaptor ();
  | (_, test) -> (* we need to synthesize a new adaptor *)
      printf "Adding test: %!";
      List.iter (Printf.printf "%Lx %!") test;
      printf "\n";
      tests := !tests @ [test];
      adapt := try_synth ();
      printf "Synthesized adaptor:\n%!";
      print_adaptor ();
      main () (* repeat *)
;;

main ();;
 


  
