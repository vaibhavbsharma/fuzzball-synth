typedef int (func)(
		   int, int, int, int, int, int,
		   int, int, int, int, int, int, int);

struct func_info {
  const char *fname;
  func *fptr;
  int num_args;
  int is_varargs;
  int is_voidret;
};

