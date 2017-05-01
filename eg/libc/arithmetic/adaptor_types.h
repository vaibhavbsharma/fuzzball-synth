#include <assert.h>

#define PER_ARG_LIM 200
#define ARITH_PER_ARG_LIM 1500000
#define ADAPTOR_STR_LEN 400

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
  int type_R;
  long val_R;
  int type_R0;
  long val_R0;
  int type_R1;
  long val_R1;
} arithsub;
