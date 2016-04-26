(* usage: synth.ml <bin> <type> <tree depth> <# outer args> <# inner args> <rand. seed> *)

open Printf
#load "str.cma"  (* used for regular expressions *)
#load "unix.cma" (* used to execute system commands *)


(*** Read command line args ***)

(* 'outer function' = the 'black box' function (f1)
   'inner function' = the function whose arguments we want to adapt (f2) *)
let print_usage () = 
  (printf "usage: synth.ml <bin> <type> <tree depth> <# outer args> <# inner args> <rand. seed>\n%!";
   printf "notes: <type> must be 'int' or 'float'\n%!";
   printf "       'outer' refers to the oracle function (f1)\n%!";
   printf "       'inner' refers to the function you're adapting (f2)\n%!";
   exit 1)
let bin = 
  try Sys.argv.(1)
  with Invalid_argument _ -> print_usage ()
let adaptor_type = 
  try let s = Sys.argv.(2) in
      if (s = "int") || (s = "float") then s
      else print_usage ()
  with Invalid_argument _ -> print_usage ()
let tree_depth = 
  try int_of_string Sys.argv.(3)
  with Invalid_argument _ -> print_usage ()
let outer_nargs = 
  try int_of_string Sys.argv.(4)
  with Invalid_argument _ -> print_usage ()
let inner_nargs =
  try int_of_string Sys.argv.(5)
  with Invalid_argument _ -> print_usage ()
let _ = 
  try Random.init (int_of_string Sys.argv.(6))
  with Invalid_argument _ -> print_usage ()


(*** current adaptor and test set ***)

(* default adaptor has all values set to 0 *)
let create_adapt num_args =
  let rec create_tree d base var_name = 
    if d > 0
    then ["-extra-condition " ^ (var_name ^ "_type_" ^ base) ^ ":reg8_t==0:reg8_t";
          "-extra-condition " ^ (var_name ^ "_val_" ^ base) ^ ":reg32_t==0:reg32_t"]
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

(* print_tests : () -> () 
   print out the current set of tests *)
let print_tests () = 
  List.iter 
    (fun test -> List.iter (fun el -> printf "%x %!" el) test; printf "\n%!") 
    !tests
  
(* print_adaptor : () -> ()
   print out the current adaptor in a readable format; note that the list of 
   operators here needs to match the list of operators in the adaptor_synthesis
   file in order for the printout to make sense; sorry for the trouble *)
let ops = ["+"; "&"; "|"; "^"; "<<"; ">>(u)"; ">>(s)"; "-"; "~"] 
let print_adaptor () =
  let slightly_better_print name v = 
        if (match_regex name ".*_type_.*")
        then if v = "0x0" 
             then "constant"
             else if v = "0x1" 
                  then "variable"
                  else "operator" 
        else v in
  List.iter (fun el -> let l = Str.split (Str.regexp " \\|:\\|=") el in
                       let name = List.nth l 1 in
                       let valu = List.nth l 4 in
                       printf "%s = %s%!\n" name (slightly_better_print name valu))
            !adapt


(*** FUZZBall command line arguments ***)

(* hardcoded path for the fevis repository *)
let fuzzball = "../../../../tools/fuzzball/exec_utils/fuzzball"

(* STP is the default for the integer adaptor; Z3 is required for floating 
   point operations (specify the path via the SOLVER environment variable) *)
let solver, solver_type, wrapper = 
  if adaptor_type = "int"
  then "../../../../tools/fuzzball/stp/stp", "stp", "./stp-wrapper"
  else try Sys.getenv "SOLVER", "z3", "./z3-wrapper"
       with Not_found -> 
         failwith "Set the location of the solver with 'export SOLVER=...'"

let main_addr = 
  match syscall ("nm " ^ bin ^ " | fgrep ' T main'") with
  | [str] -> "0x" ^ String.sub str 0 16
  | _ -> failwith "Unexpected main address format"

let input_addr =
  if adaptor_type = "int" 
  then
    let rec loop l n =
      match l with
      | [] -> (if n <> outer_nargs 
               then printf "Unexpected number of strtoul calls; something may have gone wrong\n%!" 
               else ()); []
      | (h::t) -> let x = String.make 1 (Char.chr ((Char.code 'a') + n)) in
                  ("-skip-call-ret-symbol-once 0x0" ^ (String.sub h 2 6) ^ "=" ^ x)
                  :: (loop t (n+1))
    in loop (syscall ("objdump -dr " ^ bin ^ " | grep 'call.*strtoul'")) 0
  else
    (* we assume here that the values we want to make symbolic have single
       character variable names; not great error handling... *)
    let rec loop l n =
      if n = outer_nargs
      then []
      else let x = String.make 1 (Char.chr ((Char.code 'a') + n)) in
           ("-symbolic-long 0x0" ^ (String.sub (List.hd l) 0 16) ^ "=" ^ x) 
             :: (loop (List.tl l) (n+1))
    in loop (syscall ("nm " ^ bin ^ " | grep ' B [a-z]$'")) 0

let outer_call_addr =
  match syscall ("objdump -dr " ^ bin ^ " | grep 'call.*f1'") with
  | [str1; str2] -> "0x0" ^ String.sub str2 2 6
  | _ -> failwith "Unexpected function call address formats"

let inner_func_addr = 
  match syscall ("nm " ^ bin ^ " | fgrep ' T f2'") with
  | [str] -> "0x" ^ String.sub str 0 16
  | _ -> failwith "Unexpected inner function format"

let match_jne_addr =
  match syscall ("objdump -dr " ^ bin ^ " | grep 'jne.*compare+'") with
  | [str] -> "0x" ^ String.sub str 2 6
  | _ -> 
      if adaptor_type = "int" 
      then failwith "Unexpected jne address format"
      else "" (* again, not great error handling here *)

let solver_opts = 
  "-solver smtlib-batch -save-solver-files -smtlib-solver-type " ^ solver_type

let fields = 
  let rec create_tree d base var_name =
    if d > 0
    then [(var_name ^ "_type_" ^ base, 8, format_of_string "%01x");
          (var_name ^ "_val_" ^ base, 32, format_of_string "%04x")]
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
            @ [solver_opts;"-solver-path"; solver] @ ["-arch";"x64"]
            @ ["-fuzz-start-addr"; main_addr]
            @ input_addr
            @ (if adaptor_type = "int" 
               then ["-branch-preference"; match_jne_addr ^ ":0"]
               else [])
            (*@ ["-table-limit 7"]*)
            @ ["-trace-iterations"; "-trace-assigns"; "-solve-final-pc";
               "-synthesize-adaptor"; 
               (if adaptor_type = "int" 
                then "arithmetic_int:" 
                else "arithmetic_float:") ^
               outer_call_addr ^ ":" ^ (string_of_int outer_nargs) ^ ":" ^
               inner_func_addr ^ ":" ^ (string_of_int inner_nargs)]
            @ !adapt (* representation of the adaptor as '-extra-condition' arguments *)
            @ ["-zero-memory";
               "-random-seed"; string_of_int (Random.int 10000000); 
               "--"; bin]
            @ (if adaptor_type = "int"
               then Array.to_list (Array.make outer_nargs "0")
               else []) in
  let _ = printf "%s\n%!" (String.concat " " cmd) in
  let ic = Unix.open_process_in (String.concat " " cmd) in
  let ce = ref (Array.make outer_nargs 0) in
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
               if (match_regex v "^.=0x[0-9a-f]+$") && (not (match_regex v "bfp.*"))
               then let idx = (Char.code (String.get v 0)) - (Char.code 'a') in
                    let value = int_of_string (String.sub v 2 ((String.length v) - 2)) in
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
                                    (List.map (fun el -> sprintf "%x" el) test)) 
                     !tests) in
  let testc = open_out "tests" in
  let _ = output_string testc test_str in
  let _ = close_out testc in
  let cmd = [fuzzball; "-linux-syscalls"; bin] 
            @ [solver_opts; "-solver-path"; wrapper]  @ ["-arch"; "x64"]
            @ ["-fuzz-start-addr"; main_addr]
            (*@ ["-table-limit 7"]*)
            @ ["-trace-iterations"; "-trace-assigns"; "-solve-final-pc";
               "-synthesize-adaptor"; 
               (if adaptor_type = "int" 
                then "arithmetic_int:" 
                else "arithmetic_float:") ^
               outer_call_addr ^ ":" ^ (string_of_int outer_nargs) ^ ":" ^ 
               inner_func_addr ^ ":" ^ (string_of_int inner_nargs)]
            @ (if adaptor_type = "int" 
               then ["-branch-preference"; match_jne_addr ^ ":1"]
               else []) 
            @ ["-zero-memory";
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
                    | name::_::[] when (match_regex name "bfp.*") -> ()
                        (* 'bfp' variables are internal FuzzBALL things related 
                           to floating point *)
                    | name::value::[] -> 
                        specified_vals := (name, int_of_string value) :: !specified_vals
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
            (fun (name, size, fmt) -> 
               let v = match getval !specified_vals name with 
                       | None -> 0 | Some v -> v in
               new_adaptor := !new_adaptor @
                 [sprintf "-extra-condition %s:reg%d_t==0x%x:reg%d_t"
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
  let start_ver = Unix.gettimeofday () in
  match check_adaptor () with
  | (true, _) -> (* we found a suitable adaptor *)
      let end_ver = Unix.gettimeofday () in
      printf "Time for verification: %fs\n" (end_ver -. start_ver);
      printf "Success!\nFinal test set:\n%!";
      print_tests ();
      printf "Final adaptor:\n%!";
      print_adaptor ();
  | (_, test) -> (* we need to synthesize a new adaptor *)
      let end_ver = Unix.gettimeofday () in
      printf "Time for verification: %fs\n" (end_ver -. start_ver);
      printf "Adding test: %!";
      List.iter (Printf.printf "%d %!") test;
      printf "\n";
      tests := !tests @ [test];
      let start_syn = Unix.gettimeofday () in
      let _ = adapt := try_synth () in
      let end_syn = Unix.gettimeofday () in
      printf "Time for synthesis: %fs\n" (end_syn -. start_syn);
      printf "Synthesized adaptor:\n%!";
      print_adaptor ();
      main () (* repeat *)
;;

main ();;      


  
