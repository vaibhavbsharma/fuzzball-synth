(* A fairly direct translation of synth.pl into OCaml. The only command
   line argument expected is a random seed. Note that the FUZZBALL_LOC
   and STP_LOC enviroment variables need to be set.
*)

open Printf
#load "str.cma"  (* used for regular expressions *)
#load "unix.cma" (* used to execute system commands *)


(*** Read command line args ***)

(* 'outer function' = the 'black box' function (f1)
   'inner function' = the function whose arguments we want to adapt (f2) *)
let print_usage () = 
  (printf "usage: synth.ml <bin> <# outer args> <# inner args> <rand. seed> [<lower bound for constant> <upper bound for constant>]\n%!";
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
let (const_lb, const_ub) =
  try (Sys.argv.(5), Sys.argv.(6))
  with Invalid_argument _ -> ("-1","-1")


(*** default adaptor ***)
let rec create_adapt n =
   match n with
   | 0 -> []
   | _ -> let x = String.make 1 (Char.chr ((Char.code 'a') + (n-1))) in 
          [ "-extra-condition " ^ x ^ "_is_const:reg1_t==0:reg1_t ";
           "-extra-condition " ^ x ^ "_val:reg64_t==0:reg64_t ";
	  ]
          @ create_adapt (n-1)
let adapt = ref (create_adapt inner_nargs)

let rec get_const_bounds_ec n = 
  match n with
  | 0 -> []
  | _ -> let x = String.make 1 (Char.chr ((Char.code 'a') + (n-1))) in 
          [ "-extra-condition " ^ x ^ "_val:reg64_t\>=\$" ^ const_lb ^ ":reg64_t ";
	  "-extra-condition " ^ x ^ "_val:reg64_t\<=\$" ^ const_ub ^ ":reg64_t "]
          @ get_const_bounds_ec (n-1)
let const_bounds_ec = 
  if const_lb <> const_ub then
    ref (get_const_bounds_ec inner_nargs)
  else ref []
    
let tests = ref []

(*** utility functions ***)

(* print_tests : () -> () 
   print out the current set of tests *)
let print_tests () = 
  Printf.printf "%s\n" (String.concat "\n" 
    (List.map (fun arr ->
      Array.fold_left (fun a b -> a ^ " " ^(sprintf "%Lx %!" b)) "" arr) 
    !tests))

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

let fuzzball = 
  try Sys.getenv "FUZZBALL_LOC" 
  with Not_found -> failwith "Set the location of fuzzball with 'export FUZZBALL_LOC=...'"

let stp =
  try Sys.getenv "STP_LOC" 
  with Not_found -> failwith "Set the location of stp with 'export STP_LOC=...'"

let main_addr = 
  match syscall ("nm " ^ bin ^ " | fgrep ' T main'") with
  | [str] -> "0x" ^ String.sub str 0 16
  | _ -> failwith "Unexpected main address format"

let var_addr = syscall ("objdump -dr " ^ bin ^ " | grep 'call.*strtoul'")
let rec get_skip_str list_addr n =
  (if n > 1 then get_skip_str list_addr (n-1) else "") ^
  let tmp_str = List.nth list_addr (n-1) in
  " -skip-call-ret-symbol-once 0x0" ^ 
  (String.sub tmp_str 2 6) ^
  "=x" ^ (string_of_int n) ^ " "

let outer_var_skip_str =  get_skip_str var_addr outer_nargs 

let initial_ce = (Array.fold_left 
                   (fun a b -> a ^ " " ^ (string_of_int b)) ""
                   (Array.make outer_nargs 0))

let outer_call_addr =
  match syscall ("objdump -dr " ^ bin ^ " | grep 'call.*f1'") with
  | [str1; str2] -> "0x0" ^ String.sub str2 2 6
  | _ -> failwith "Unexpected x and y address formats"

let inner_func_addr = 
  match syscall ("nm " ^ bin ^ " | fgrep ' T f2'") with
  | [str] -> "0x" ^ String.sub str 0 16
  | _ -> failwith "Unexpected main address format"

let match_jne_addr =
  match syscall ("objdump -dr " ^ bin ^ " | grep 'jne.*compare+'") with
  | [str] -> "0x" ^ String.sub str 2 6
  | _ -> failwith "Unexpected jne address format"

let solver_opts = ["-solver"; "smtlib"; "-solver-path"; stp]

let fields = 
  let rec fields_loop n =
    let var_name = String.make 1 (Char.chr ((Char.code 'a')+n)) in
    (if n <> 0 then fields_loop (n-1) else []) @
    [(var_name^"_is_const",1,format_of_string "%01x");
     (var_name^"_val",64,format_of_string "%08x")]
  in
fields_loop (inner_nargs-1)

(*** check_adaptor : () -> (bool * (int * int))
     given the specification of an adaptor, execute it with symbolic
     inputs to either check it, or produce a counterexample ***)
let check_adaptor () = 
  let cmd = [fuzzball; "-linux-syscalls"; bin; ] 
            @ solver_opts @["-arch";"x64"]
            @ ["-fuzz-start-addr"; main_addr; 
               outer_var_skip_str;
               "-branch-preference"; match_jne_addr ^ ":0";
               "-trace-iterations"; "-trace-assigns"; "-solve-final-pc"; 
               "-synthesize-adaptor";
               "simple:" ^ 
               outer_call_addr ^ ":" ^ (string_of_int outer_nargs) ^ ":" ^
               inner_func_addr ^ ":" ^ (string_of_int inner_nargs)]
    @ !adapt (* contains adaptor as -extra-condition's *)
    @ !const_bounds_ec
            @ ["-zero-memory";
               "-random-seed"; string_of_int (Random.int 10000000); 
               "--"; bin; initial_ce] in
  Printf.printf "%s\n" (String.concat " " cmd); 
  let log = syscall (String.concat " " cmd) in
  let ce = ref (Array.make outer_nargs 0L) in
  (* read_results : string list -> (int * int) -> bool -> (bool * (int * int))
     read through the results of the call to FuzzBALL keeping track of
     the number of matches and mismatches, and record a counterexample
     for the first mismatch *)
  let rec read_results log (matches, fails) this_ce = 
    match log with
    | [] -> 
        if matches = 0 && fails = 0 
        then failwith "Missing results from check run"
        else (true, !ce)
    | (line::rest) -> 
        printf "  %s\n%!" line;
        match line with
        | "Match" -> read_results rest (matches + 1, fails) this_ce
        | "Mismatch" -> read_results rest (matches, fails + 1) true
        | _ when (match_regex line "^Input vars: .*$") && this_ce ->
            (* use regular expressions to pull out values for x and y;
               if no values for x and y are specified, assume that they are 0 *)
            List.iter 
              (fun v ->
                 if (match_regex v "^x[0-9]=0x[0-9a-f]+$") 
                 then 
                      let arg_num = int_of_string (String.sub v 1 1) in
                      let arg_val = Int64.of_string (String.sub v 3 
                                                     ((String.length v) - 3)) in
                      Array.set !ce (arg_num-1) arg_val)
              (Str.split (Str.regexp " ") line);
              (* after updating ce once, we are done and should return *)
              (false, !ce)
        | _ -> read_results rest (matches, fails) this_ce in
  read_results log (0, 0) false


(*** try_synth : () -> (string,string)
     given a set of tests, run with the adaptor symbolic to see if we can
     synthesize an adaptor that works for those tests ***)
let try_synth () = 
  let test_str = String.concat "\n" 
    (List.map (fun arr ->
      Array.fold_left (fun a b -> a ^ " " ^ (sprintf "%Lx" b)) "" arr) 
    !tests) in
  let testc = open_out "tests" in
  let _ = output_string testc test_str in
  let _ = close_out testc in
  let cmd = [fuzzball; "-linux-syscalls"; bin] 
            @ solver_opts  @["-arch";"x64"]
            @ ["-fuzz-start-addr"; main_addr]
            @ ["-trace-iterations"; "-trace-assigns"; "-solve-final-pc"; 
               "-synthesize-adaptor";
               "simple:" ^ 
               outer_call_addr ^ ":" ^ (string_of_int outer_nargs) ^ ":" ^ 
               inner_func_addr ^ ":"^(string_of_int inner_nargs);]
	      @ !const_bounds_ec
              @ ["-branch-preference"; match_jne_addr ^ ":1";
               "-zero-memory";
               "-random-seed"; string_of_int (Random.int 10000000);
               "--"; bin; "tests"] in
  (*Printf.printf "%s\n" (String.concat " " cmd);
  Printf.printf "%s\n" outer_call_addr ;
  Printf.printf "%s\n" inner_func_addr ;*)
  let log = syscall (String.concat " " cmd) in
  (* read_results : string list -> bool -> (string,string)
     read through the results of the call to FuzzBALL looking for a case
     where all test are successfully passed *)
  let rec read_results log success = 
    match log with
    | [] -> 
        if (not success) 
        then (printf "Synthesis failure: seems the functions are not equivalent.\n%!";
              exit 2)
        else []
    | (line::rest) -> 
        if not (match_regex line "^Input vars: .*$")
        then printf "  %s\n%!" line
        else ();
        match line with 
        | "All tests succeeded!" -> read_results rest true
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
                          specified_vals := (name,value) :: !specified_vals
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
              (fun(name, size, _ ) ->
                 match getval !specified_vals name with
                 | None -> 
                   new_adaptor := !new_adaptor @ 
                   [sprintf "-extra-condition %s:reg%d_t==%s:reg%d_t" 
                      name size "0x00000000" size]
                 | Some v -> 
                   new_adaptor := !new_adaptor @
                   [sprintf "-extra-condition %s:reg%d_t==%s:reg%d_t" 
                     name size v size])
              fields;
              (*Printf.printf "new_adaptor = %s\n" 
                (String.concat " " !new_adaptor);*)
            !new_adaptor 
        | _ -> read_results rest success in
  read_results log false


(*** main : () -> ()
     start with a simple adaptor and no tests and alternate between test 
     generation and synthesis, updating the adaptor and test set as needed ***)
let rec main () =
  let () = printf "Checking synthesized adaptor\n%!" in
  match check_adaptor () with
  | (true, _) -> (* we found a suitable adaptor *)
      printf "Success!\nFinal test set:\n%!";
      print_tests ();
      printf "Final adaptor:\n%!";
      print_adaptor ();
  | (_, arg_array) -> (* we need to synthesize a new adaptor *)
      printf "Mismatch on inputs ";
      Array.iter (Printf.printf "%Ld %!") arg_array;
      printf "adding as test\n";
      tests := !tests @ [arg_array];
      adapt := try_synth ();
      printf "Synthesized adaptor:\n%!";
      print_adaptor ();
      main () (* repeat *)
;;

main ();;
