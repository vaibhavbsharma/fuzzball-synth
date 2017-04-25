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

