#ifndef _ADAPTOR_TYPES_H
#define _ADAPTOR_TYPES_H
typedef struct {
  int var_is_const;
  long var_val;
} argsub;

typedef struct {
  int ret_type;
  long ret_val;
} retsub;

typedef struct {
  argsub a_ad[13];
  retsub r_ad;
} argret;

typedef struct {
  int var_type;
  long var_val;
} arithd1;


// had to make this a struct of 6 items instead of a recursive struct with left and right nodes because each arithmetic adapter is printed as a list of 6 items in synth-arithmetic-frag.pl
typedef struct {
  int this_var_type;
  long this_var_val;
  int left_var_type;
  long left_var_val;
  int right_var_type;
  long right_var_val;
} arithd2;

typedef struct {
  arithd2 arith[13];
  retsub r_ad;
} arithd2ret;
#endif
