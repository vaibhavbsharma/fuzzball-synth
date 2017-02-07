#include <stdlib.h>
#include <stdio.h>

int f1(int a) {
  if(a == 0)
    return 1;
  else
    return 10;
}

int f2(int a) __attribute((__annotate__(("fla"))));
int f2(int a) __attribute((__annotate__(("bcf"))));
int f2(int a) {
  if(a == 0)
    return 1;
  else
    return 10;
}

int main(int argc, char** argv) {
  int a = atoi(argv[1]);
  printf("%d %d %d\n", f1(a), f2(a), (f1(a)==f2(a)));
  return 0;
}
