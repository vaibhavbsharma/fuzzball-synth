open Printf
#load "str.cma"  (* used for regular expressions *)
#load "unix.cma" (* used to execute system commands *)


(*** Read command line args ***)

(* 'outer function' = the 'black box' function (f1)
   'inner function' = the function whose arguments we want to adapt (f2) *)
let print_usage () = 
  (printf "usage: synth.ml <bin> <string length> <rand. seed>\n%!";
   exit 1)
let bin = 
  try Sys.argv.(1)
  with Invalid_argument _ -> print_usage ()
let string_length = 
  try int_of_string Sys.argv.(2)
  with Invalid_argument _ -> print_usage ()
let _ = 
  try Random.init (int_of_string Sys.argv.(3))
  with Invalid_argument _ -> print_usage ()


(*** default adaptor ***)
let rec create_adapt n =
   match n with
   | -1 -> []
   | _ ->  [ "-extra-condition tableX" ^ (sprintf "%02x" n) ^ ":reg8_t==0:reg8_t "]
          @ create_adapt (n-1)
let adapt = ref (create_adapt 255)

let tests = ref []

(*** utility functions ***)

(* print_tests : () -> () 
   print out the current set of tests *)
let print_tests () = 
  Printf.printf "%s\n" (String.concat "\n" 
			  (List.map 
			     (fun arr -> Array.fold_left 
			       (fun a b -> 
				 a ^ (sprintf "\\x%Lx" b)) 
			       "" arr) 
			     !tests))

(* print_adaptor : () -> ()
   print out the current adaptor in a readable format *)
let print_adaptor () =
  List.iter (fun el -> let l = Str.split (Str.regexp " \\|:\\|=") el in
                       printf "%s%! " (List.nth l 4))
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

let var_addr = 
  match syscall ("nm " ^ bin ^ " | fgrep 'B the_input'") with
  | [str] -> "0x" ^ String.sub str 0 16
  | _ -> failwith "Unexpected the_input address format"
let outer_var_skip_str = "-symbolic-cstring " ^ var_addr ^ 
  "+" ^ (string_of_int string_length)

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
    let var_name = (Printf.sprintf "%02x" (n-1)) in
    (if n <> 0 then fields_loop (n-1) else []) @
    [("tableX"^var_name,8,format_of_string "%01x");]
  in
  fields_loop 256

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
               "chartrans:" ^ 
               outer_call_addr ^ ":" ^ (string_of_int string_length) ^ ":" ^
               inner_func_addr ^ ":" ^ (string_of_int string_length)]
            @ !adapt (* contains adaptor as -extra-condition's *)
            @ ["-zero-memory";
               "-random-seed"; string_of_int (Random.int 10000000); 
               "--"; bin; "s"] in
  (* Printf.printf "%s\n" (String.concat " " cmd); *)
  let log = syscall (String.concat " " cmd) in
  let ce = ref (Array.make 64 0L) in
  (* let ce = ref (Array.make string_length 0L) in *)
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
                 if (match_regex v "^input0_[0-9]=0x[0-9a-f]+$") 
                 then 
                   let arg_num = int_of_string (String.sub v 7 1) in
                   let arg_val = Int64.of_string (String.sub v 9 
                                                    ((String.length v) - 9)) in
                   Array.set !ce arg_num arg_val)
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
      Array.fold_left (fun a b -> 
	a ^ (sprintf "%c" (Char.chr (Int64.to_int b)))) 
	"" arr) 
    !tests) in
  let testc = open_out "tests" in
  let _ = output_string testc test_str in
  let _ = close_out testc in
  let cmd = [fuzzball; "-linux-syscalls"; bin] 
            @ solver_opts  @["-arch";"x64"]
            @ ["-fuzz-start-addr"; main_addr]
            @ ["-trace-iterations"; "-trace-assigns"; "-solve-final-pc"; 
               "-synthesize-adaptor";
               "chartrans:" ^ 
               outer_call_addr ^ ":" ^ (string_of_int string_length) ^ ":" ^ 
               inner_func_addr ^ ":"^(string_of_int string_length);
               "-branch-preference"; match_jne_addr ^ ":1";
               "-zero-memory";
               "-random-seed"; string_of_int (Random.int 10000000);
               "--"; bin; "f tests"] in
  (* Printf.printf "%s\n" (String.concat " " cmd);
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
      Array.iter (Printf.printf "\\x%Lx%!") arg_array;
      printf "adding as test\n";
      tests := !tests @ [arg_array];
      adapt := try_synth ();
      printf "Synthesized adaptor:\n%!";
      print_adaptor ();
      main () (* repeat *)
;;

main ();;
