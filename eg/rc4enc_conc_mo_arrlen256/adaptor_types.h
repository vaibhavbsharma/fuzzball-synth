#ifndef _ADAPTOR_TYPES_H
#define _ADAPTOR_TYPES_H

#define PER_ARG_LIM 1000
#define ADAPTOR_STR_LEN 600
typedef struct {
  int var_is_const;
  long var_val;
} argsub;

typedef struct {
  int ret_type;
  long ret_val;
} retsub;

typedef struct {
  argsub a_ad[6];
  retsub r_ad;
} argret;

typedef struct {
  unsigned long long int type;
  int size;
  int n;
} fieldsub;

#endif
