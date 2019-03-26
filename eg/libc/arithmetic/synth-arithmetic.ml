(* usage: synth.ml <bin> <type> <tree depth> <# outer args> <# inner args> <rand. seed> *)

open Printf
open String
(*#load "str.cma"  (* used for regular expressions *)
  #load "unix.cma" (* used to execute system commands *)*)


(*** Read command line args ***)

(* 'outer function' = the 'black box' function (f1)
   'inner function' = the function whose arguments we want to adapt (f2) *)
let print_usage () = 
  (printf "usage: synth.ml <bin> <type> <tree depth> <f1num> <f2num> <rand. seed> <verbose>\n%!";
   printf "notes: <type> must be 'int' or 'float'\n%!";
   printf "       'outer' refers to the oracle function (f1)\n%!";
   printf "       'inner' refers to the function you're adapting (f2)\n%!";
   printf "       verbose=1 turns on printing of debugging outputs, use verbose=0 for minimal debugging output\n%!";
   exit 1)
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
let f1num = 
  try int_of_string Sys.argv.(4)
  with Invalid_argument _ -> print_usage ()
let f2num =
  try int_of_string Sys.argv.(5)
  with Invalid_argument _ -> print_usage ()
let _ = 
  try Random.init (int_of_string Sys.argv.(6))
  with Invalid_argument _ -> print_usage ()
let verbose =
  try int_of_string Sys.argv.(7)
  with Invalid_argument _ -> print_usage ()

let func_info = ref []
let in_chan = (open_in "types-no-float-1204.lst")
let _ =
  (try 
    while true; do
      let line = input_line in_chan in
      let field_list = (Str.split (Str.regexp_string " ") line) in
      let fname = (List.nth field_list 2) in
      let nargs = 
	int_of_string (if (String.length (List.nth field_list 1)) = 2 then
	  (Str.string_before (List.nth field_list 1) 1)
	else (List.nth field_list 1) )
      in
      func_info := !func_info @ [(fname, nargs)];
      (*Printf.printf "%s(%d)\n" fname nargs; *)
    done;
   with End_of_file ->
     close_in in_chan;)

let (f1name, outer_nargs) = (List.nth !func_info f1num) 
let (f2name, inner_nargs) = (List.nth !func_info f2num) 
 
(*** current adaptor and test set ***)

(* default adaptor has all values set to 0 *)
let create_adapt num_args =
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
(* let adapt = ref ["-extra-condition"; "a_type_R:reg8_t==2:reg8_t";
		 "-extra-condition"; "a_val_R:reg64_t==0:reg64_t";
		 "-extra-condition"; "a_type_R0:reg8_t==1:reg8_t";
		 "-extra-condition"; "a_val_R0:reg64_t==0:reg64_t"; 
		 "-extra-condition"; "a_type_R1:reg8_t==0:reg8_t";
		 "-extra-condition"; "a_val_R1:reg64_t==0x20:reg64_t";
		] *)

let tests = ref [] (* will be a list of lists *)


(*** utility functions ***)

(* match_regex : string -> string -> bool 
   check that a string matches the provided regex *)
let match_regex str regex =
  Str.string_match (Str.regexp regex) str 0


(* print_tests : () -> () 
   print out the current set of tests *)
let print_tests () = 
  List.iter 
    (fun test -> List.iter (fun el -> printf "%Lx %!" el) test; printf "\n%!") 
    !tests
  
(* print_adaptor : () -> ()
   print out the current adaptor in a readable format; note that the list of 
   operators here needs to match the list of operators in the adaptor_synthesis
   file in order for the printout to make sense; sorry for the trouble *)
let print_adaptor () =
  List.iter (fun el -> let l = Str.split (Str.regexp " \\|:\\|=") el in
                       let name = List.nth l 1 in
                       let valu = List.nth l 4 in
                       printf "%s = %s%! " name valu)
            !adapt


(*** FUZZBall command line arguments ***)

let fuzzball = "fuzzball"

(* STP is the default for the integer adaptor; Z3 is required for floating 
   point operations (specify the path via the SOLVER environment variable) *)
let solver, solver_type, wrapper = 
  if adaptor_type = "int"
  (*then "stp", "stp", "./stp-wrapper"*)
  then "stp", "stp", "stp"
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
                  ("-symbolic-long 0x0" ^ (String.sub h 0 16) ^ "=" ^ x)
                  (*("-skip-call-ret-symbol-once 0x0" ^ (String.sub h 2 6) ^ "=" ^ x)*)
                  :: (loop t (n+1))
    in loop (syscall ("nm " ^ bin ^ " | fgrep \" B global_arg\" ")) 0
    (*in loop (syscall ("objdump -dr " ^ bin ^ " | grep 'call.*strtoul'")) 0*)
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

let f1_call_addr =
  match syscall ("objdump -dr " ^ bin ^ " | grep 'call.*<f1>'") with
  | [str1] -> "0x0" ^ String.sub str1 2 6
  | _ -> failwith "Unexpected f1 function call address format"
let f2_call_addr =
  match syscall ("objdump -dr " ^ bin ^ " | grep 'call.*<wrap_f2>'") with
  | [str1] -> "0x0" ^ String.sub str1 2 6
  | _ -> failwith "Unexpected f1 function call address format"

let post_f1_call_addr = (Printf.sprintf "0x%x" ((int_of_string f1_call_addr)+5))

let post_f2_call_addr = (Printf.sprintf "0x%x" ((int_of_string f2_call_addr)+5))

let inner_func_addr = 
  match syscall ("nm " ^ bin ^ " | fgrep ' T f2'") with
  | [str] -> "0x" ^ String.sub str 0 16
  | _ -> failwith "Unexpected inner function format"

let match_jne_addr =
  match syscall ("objdump -dr " ^ bin ^ " | grep 'jne.*<compare+'") with
  | [str] -> "0x" ^ String.sub str 2 6
  | _ -> 
      if adaptor_type = "int" 
      then failwith "Unexpected jne address format"
      else "" (* again, not great error handling here *)

let solver_opts = 
  "-solver smtlib-batch -smtlib-solver-type " ^ solver_type

let fields = 
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

let synth_opt = 
  "-synthesize-adaptor " ^ 
  (if adaptor_type = "int" 
   then " arithmetic_int:" 
   else " arithmetic_float:") ^
   f2_call_addr ^ ":" ^ (string_of_int outer_nargs) ^ ":" ^
   inner_func_addr ^ ":" ^ (string_of_int inner_nargs)

let path_depth_limit = 300
let iteration_limit = 4000

(*** check_adaptor : () -> (bool * (int * int))
     given the specification of an adaptor, execute it with symbolic
     inputs to either check it, or produce a counterexample ***)
let check_adaptor () = 
  let cmd = 
    [fuzzball; "-linux-syscalls"; "-arch x64"; bin;
     solver_opts; "-solver-path"; solver;
     "-fuzz-start-addr"; main_addr]
    @ input_addr
    @ (if adaptor_type = "int" 
      then ["-branch-preference"; match_jne_addr ^ ":0"]
      else [])
    @ ["-match-syscalls-in-addr-range"; 
       f1_call_addr ^ ":" ^ post_f1_call_addr ^ ":" ^
         f2_call_addr ^ ":" ^ post_f2_call_addr;
       "-trace-iterations"; "-trace-assigns"; "-solve-final-pc";
       "-no-fail-on-huer"; (* not the right way to make strange term failures go away
			      but it works for now, TODO: fix this in the near future *)
       synth_opt]
    @ !adapt (* representation of the adaptor as '-extra-condition' arguments *)
    @ (if verbose = 1 then
	["-trace-decisions"; "-trace-conditions"; "-trace-binary-paths";"-trace-tables"]
      else [])
    @ [(*"-table-limit 8";*)
      "-zero-memory";
      (* "-trace-temps"; 
      "-trace-solver";
      "-trace-sym-addrs";
      "-trace-sym-addr-details";
      "-trace-insns";
      "-trace-registers"; *)
       "-random-seed"; string_of_int (Random.int 10000000); 
       "-trace-stopping";
       "--"; bin; string_of_int f1num; 
       string_of_int f2num; "g"]
  in
  let _ = if verbose = 1 then printf "%s\n%!" (String.concat " " cmd) else () in
  let ic = Unix.open_process_in (String.concat " " cmd) in
  let ce = ref (Array.make 6 0L) in
  (* read_results : string list -> (int * int) -> bool -> (bool * (int * int))
     read through the results of the call to FuzzBALL keeping track of
     the number of matches and mismatches, and record a counterexample
     for the first mismatch *)
  let rec read_results (matches, fails) record_ce f1_completed = 
    try
      let line = input_line ic in
      let no_print = ["Completed f1"; "Completed f2"; 
                      "Recording Linux.x86-64 system call.*";
                      "Starting f1"; "Starting f2";
                      "f1:syscall.*"; "f2:syscall.*"] in
      let _ = if not (List.fold_left (||) 
                        false 
                        (List.map (fun s -> match_regex line s) no_print))
              then (if verbose = 1 then printf " %s\n%!" line else ())
              else () in
      match line with
      | "Match" -> read_results (matches + 1, fails) record_ce f1_completed
      | "Completed f1" -> read_results (matches, fails) record_ce true
      | "Mismatch" -> read_results (matches, fails + 1) true f1_completed
      | _ when (match_regex line ".*total query time =.*") || 
      (match_regex line ".*Query time =.*") ||
      (match_regex line ".*Starting new query.*") ||
      (match_regex line ".*Fatal error.*") ->
        printf " %s\n%!" line;
        read_results (matches, fails) record_ce f1_completed
      | _ when (match_regex line "Stopping at null deref at 0x[0-9a-f]+") && f1_completed ->
            read_results (matches, fails + 1) true f1_completed
      | _ when (match_regex line "Stopping at access to unsupported address at 0x[0-9a-f]+") 
                  && f1_completed ->
            read_results (matches, fails + 1) true f1_completed
      | _ when (match_regex line "Stopping on disqualified path at 0x[0-9a-f]+") 
                  && f1_completed ->
            read_results (matches, fails + 1) true f1_completed
      | _ when (match_regex line "Disqualified path at 0x[0-9a-f]+") 
                  && f1_completed ->
            read_results (matches, fails + 1) true f1_completed
      | _ when (match_regex line "^Input vars: .*$") && record_ce ->
          (* use regular expressions to pull out values for a, b and c;
             if no values for x and y are specified, assume that they are 0 *)
          List.iter 
            (fun v ->
               if (match_regex v "^.=0x[0-9a-f]+$") && (not (match_regex v "bfp.*"))
               then let idx = (Char.code (String.get v 0)) - (Char.code 'a') in
                    let value = Int64.of_string (String.sub v 2 ((String.length v) - 2)) in
                    Array.set !ce idx value
               else ())
            (Str.split (Str.regexp " ") line);
            (* after updating ce once, we are done *)
            let _ = Unix.close_process_in ic in
            (false, Array.to_list !ce)
      | _ -> read_results (matches, fails) record_ce f1_completed
    with End_of_file -> 
      let _ = Unix.close_process_in ic in
      if matches = 0 && fails = 0 
      then (printf "CounterExample search failed\n"; 
        failwith "Missing results from check run")
      else (true, Array.to_list !ce) in
  read_results (0, 0) false false


(*** try_synth : () -> string
     given a set of tests, run with the adaptor symbolic to see if we can
     synthesize an adaptor that works for those tests ***)
let try_synth () = 
  let test_str = 
    String.concat "\n"  
      (List.map 
         (fun test -> String.concat " " 
           (List.map (fun el -> sprintf "%Lx" el) test)) 
         !tests) in
  let testc = open_out "tests" in
  let _ = output_string testc test_str in
  let _ = close_out testc in
  let cmd = 
    [fuzzball; "-linux-syscalls"; "-arch x64"; bin;
     solver_opts; "-solver-path"; wrapper;
     "-fuzz-start-addr"; main_addr]
    @ (if adaptor_type = "int" 
      then ["-branch-preference"; match_jne_addr ^ ":1"]
      else []) 
    @ ["-match-syscalls-in-addr-range";
       f1_call_addr ^ ":" ^ post_f1_call_addr ^ ":" ^
         f2_call_addr ^ ":" ^ post_f2_call_addr;
       "-return-zero-missing-x64-syscalls";
       "-adaptor-search-mode";
       "-trace-sym-addrs";
       "-trace-sym-addr-details";
      "-trace-iterations"; "-trace-assigns"; "-solve-final-pc";
      "-no-fail-on-huer"; (* not the right way to make strange term failures go away
			  but it works for now, TODO: fix this in the near future *)
      synth_opt;
      (*"-table-limit 8";*)
      "-zero-memory";
      "-random-seed"; string_of_int (Random.int 10000000);
      "--"; bin; string_of_int f1num; string_of_int f2num; "f tests"] in
  let _ = (if verbose = 1 then printf "%s\n%!" (String.concat " " cmd) else ()) in
  let ic = Unix.open_process_in (String.concat " " cmd) in
  (* read_results : string list -> bool -> string
     read through the results of the call to FuzzBALL looking for a case
     where all test are successfully passed *)
  let rec read_results success = 
    try
      let line = input_line ic in
      let no_print = ["Completed f1"; "Completed f2"; 
                      "Recording Linux.x86-64 system call.*";
                      "Starting f1"; "Starting f2";
                      "f1:syscall.*"; "f2:syscall.*";
                      "^Input vars: .*$"] in
      let _ = if not (List.fold_left (||) 
                        false 
                        (List.map (fun s -> match_regex line s) no_print))
              then (if verbose = 1 then printf " %s\n%!" line else ())
              else () in
      match line with 
      | "All tests succeeded!" -> read_results true
      | _ when (match_regex line ".*total query time =.*") ||
      (match_regex line ".*Query time =.*") ||
      (match_regex line ".*Starting new query.*") ||
      (match_regex line ".*Fatal error.*") ->
        printf " %s\n%!" line;
        read_results success
      | _ when (match_regex line "Disqualified path at 0x[0-9a-f]+") ->
	read_results false
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

let total_ce_time = ref 0.0
let total_as_time = ref 0.0
let start_process = Unix.gettimeofday ()
  
(*** main : () -> ()
     start with a simple adaptor and no tests and alternate between test 
     generation and synthesis, updating the adaptor and test set as needed ***)
let rec main () =
  let start_ver = Unix.gettimeofday () in
  match check_adaptor () with
  | (true, _) -> (* we found a suitable adaptor *)
      let end_ver = Unix.gettimeofday () in
      printf "Time for verification: %fs\n" (end_ver -. start_ver);
      printf "elapsed time = %fs, last CE search time = %fs\n" (end_ver -. start_process) (end_ver -. start_ver);
      total_ce_time := !total_ce_time +. (end_ver -. start_ver);
      printf "Success!\nFinal test set:\n%!";
      print_tests ();
      printf "Final adaptor: %!";
      print_adaptor ();
  | (_, test) -> (* we need to synthesize a new adaptor *)
      let end_ver = Unix.gettimeofday () in
      printf "Time for verification: %fs\n" (end_ver -. start_ver);
      printf "elapsed time = %fs, last CE search time = %fs\n" (end_ver -. start_process) (end_ver -. start_ver);
      total_ce_time := !total_ce_time +. (end_ver -. start_ver);
      printf "Adding test: %!";
      List.iter (Printf.printf "%Ld %!") test;
      printf "\n";
      tests := !tests @ [test];
      let start_syn = Unix.gettimeofday () in
      let _ = adapt := try_synth () in
      let end_syn = Unix.gettimeofday () in
      printf "Time for synthesis: %fs\n" (end_syn -. start_syn);
      printf "elapsed time = %fs, last AS search time = %fs\n" (end_syn -. start_process) (end_syn -. start_syn);
      total_as_time := !total_as_time +. (end_syn -. start_syn);
      printf "Synthesized adaptor:\n%!";
      print_adaptor ();
      main () (* repeat *)
;;
ignore(syscall("rm str_arg*"));
ignore(syscall("rm -rf fuzzball-tmp-*"));
Printf.printf "main: %s\n" main_addr;
Printf.printf "f1: %s\n" f2_call_addr;
Printf.printf "f2: %s\n" inner_func_addr;

List.iteri (fun idx str -> Printf.printf "arg %d = %s\n" idx str;) input_addr;

Printf.printf "branch: %s\n" match_jne_addr;
Printf.printf "%d = %s(%d)\n" f1num f1name outer_nargs;
Printf.printf "%d = %s(%d)\n" f2num f2name inner_nargs;

Printf.printf "Checking initial adapter: ";
print_adaptor ();

main ();;      
printf "\n";
printf "Total CE time = %fs\n" !total_ce_time;
printf "Total AS time = %fs\n" !total_as_time;
  
