#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>

long double factorial[15]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200};

long double const_lb = 0x080000000;
long double const_ub = 0x07ffffffe;
long double f1nargs = 13;
int f2nargs = 13;

long double my_pow(long double a, long double b) {
  long double ret=1;
  while(b--!=0) {
    ret *= a;
  }
  return ret;
}

long double perm(int n, int r) {
  if(n-r < 0) return perm(r,n);
  assert(n<=13);
  assert(n-r>=0);
  return factorial[n]/factorial[n-r]; 
}

long double comb(int n, int r) { 
  assert(n<=13);
  assert(r<=13);
  assert(n-r>=0);
  return factorial[n]/(factorial[n-r] * factorial[r]); 
}

long double num_argperm() {
  int k;
  long double ret = comb(f1nargs, f2nargs);
  ret *= perm(f2nargs, f2nargs);
  long double R = 8; //8*f2nargs + 9 + D + 1;
  return ret * R;
}

long double num_argsub() {
  int k;
  long double ret=0;
  long double D = const_ub + llabs(const_lb) + 1;
  for(k=0; k<=f1nargs; k++) {
    long double a=my_pow(D, f2nargs - k);
    a = a * comb(f1nargs, k);
    a = a * perm(f2nargs, k);
    ret += a;
    //printf("%Lf ", ret);
  }
  //printf("\n");
  long double R = 8; //8*f2nargs + 9 + D + 1;
  return ret * R;
}

long double num_typeconv() {
  int k;
  long double ret=0;
  long double D = const_ub + llabs(const_lb) + 1;
  for(k=0; k<=f1nargs; k++) {
    long double a=my_pow(D, f2nargs - k);
    a = a * comb(f1nargs, k);
    a = a * perm(f2nargs, k) * my_pow(8, k);
    ret += a;
  }
  long double R = 8;
  return ret * R;
}

int main() {
  printf("%4.3Lf\n", num_argperm());
  printf("%4.3Lf\n", num_argsub());
  printf("%4.3Lf\n", num_typeconv());
  return 0;
}

// 49816166400.000
// 1353842673256133613672836069744979715007575881745542100533472072609341944172474754457000677933949792966627943690376056594759680.000
// 1353843046156775475576961335967398513720713718511049341688509589102330775617719636646726527171614403121281965764145131592613888.000
