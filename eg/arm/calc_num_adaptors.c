#include <stdio.h>
#include <assert.h>
#include <limits.h>

unsigned long long int factorial[15]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200};

int const_lb = 0x80000000;
int const_ub = 0x7fffffff;
int f1nargs = 13;
int f2nargs = 13;

unsigned long long int my_pow(unsigned long long int a, unsigned long long int b) {
  unsigned long long int ret=1;
  while(b--!=0) {
    ret *= a;
  }
  return ret;
}

unsigned long long int perm(int n, int r) {
  if(n-r < 0) return perm(r,n);
  assert(n<=13);
  assert(n-r>=0);
  return factorial[n]/factorial[n-r]; 
}

unsigned long long int comb(int n, int r) { 
  assert(n<=13);
  assert(r<=13);
  assert(n-r>=0);
  return factorial[n]/(factorial[n-r] * factorial[r]); 
}

unsigned long long int calc_total_adaptor_num_argsub() {
  int k;
  unsigned long long int ret=0;
  unsigned long long int D = const_ub - const_lb + 1;
  for(k=0; k<=f1nargs; k++) {
    unsigned long long int a=my_pow(D, f2nargs - k);
    a = a * comb(f1nargs, k);
    a = a * perm(f2nargs, k);
    ret += a;
  }
  unsigned long long int R = 1; //8*f2nargs + 9 + D + 1;
  return ret * R;
}

unsigned long long int calc_total_adaptor_num_typeconv() {
  int k;
  unsigned long long int ret=0;
  unsigned long long int D = const_ub - const_lb + 1;
  for(k=0; k<=f1nargs; k++) {
    unsigned long long int a=my_pow(D, f2nargs - k);
    a = a * comb(f1nargs, k);
    a = a * perm(f2nargs, k) * my_pow(8, k);
    ret += a;
  }
  unsigned long long int R = 8;
  return ret * R;
}

int main() {
  printf("%llu\n", calc_total_adaptor_num_argsub());
  printf("%llu\n", calc_total_adaptor_num_typeconv());
  return 0;
}
