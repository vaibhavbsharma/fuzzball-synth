#ifndef _CALC_NUM_ADAPTORS_H
#define _CALC_NUM_ADAPTORS_H

extern int const_ub, const_lb, f1nargs, f2nargs;

long factorial[11]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

long my_pow(long a, long b) {
  long ret=1;
  while(b--!=0) {
    ret *= a;
  }
  return ret;
}

long perm(int n, int r) {
  if(n-r < 0) return perm(r,n);
  assert(n<=10);
  assert(n-r>=0);
  return factorial[n]/factorial[n-r]; 
}

long comb(int n, int r) { 
  assert(n<=10);
  assert(r<=10);
  assert(n-r>=0);
  return factorial[n]/(factorial[n-r] * factorial[r]); 
}

long calc_total_adaptor_num_argsub() {
  int k;
  long ret=0;
  long D = const_ub - const_lb + 1;
  for(k=0; k<=f1nargs; k++) {
    long a=my_pow(D, f2nargs - k);
    a = a * comb(f1nargs, k);
    a = a * perm(f2nargs, k);
    ret += a;
  }
  long R = 8*f2nargs + 9 + D + 1;
  return ret * R;
}

long calc_total_adaptor_num_typeconv() {
  int k;
  long ret=0;
  long D = const_ub - const_lb + 1;
  for(k=0; k<=f1nargs; k++) {
    long a=my_pow(D, f2nargs - k);
    a = a * comb(f1nargs, k);
    a = a * perm(f2nargs, k) * my_pow(10, k);
    ret += a;
  }
  long R = 8*f2nargs + 9 + D + 1;
  return ret * R;
}
#endif