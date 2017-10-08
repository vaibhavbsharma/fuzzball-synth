#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "vlc_candidates_filtered.h"

using namespace std;

int _ref3(int x) {
  return (x ^ (x >> 31)) - (x >> 31);
}

int _ref5(unsigned short x) {
  return ((x << 16) >> 24);
}

int main() {
  //printf("0x%x\n", ref1(0xffffffff));
  //printf("0x%x\n", ref1(0));
  //printf("0x%x, 0x%x\n", _ref3(-1), ref3(-1));
  //printf("0x%x, 0x%x\n", _ref3(-2), ref3(-2));
  //printf("0x%x, 0x%x\n", _ref3(1), ref3(1));
  //printf("0x%x, 0x%x\n", _ref3(2), ref3(1));
  //printf("0x%x, 0x%x\n", _ref3(0x80000000), ref3(0x80000000));
  //printf("0x%x, 0x%x\n", _ref3(0xffffffff), ref3(0xffffffff));
  //printf("0x%x, 0x%x\n", _ref5(257), (unsigned char)(ref5(257)));
  for(unsigned int i = 0; i < (1<<31)+(1<<30); i++) {
    if(ref2(i) != ref15(i)) {
      printf("%u, 0x%x, 0x%x\n", i, ref2(i), ref15(i));
    }
  }
}
