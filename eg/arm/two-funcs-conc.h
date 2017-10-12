#include "all_adapters.h"
#include "test1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <boost/algorithm/clamp.hpp>
#include "vlc_candidates_filtered.h"

int identity_fn(int val, int lo, int hi, int a) {
  return val;
}

extern "C" int clamp32(int x, int lo, int hi) {
    return boost::algorithm::clamp(x, lo, hi);
}

short clamp16(short x, short lo, short hi) {
    return boost::algorithm::clamp(x, lo, hi);
}

extern "C" int boost_clamp(int val, int lo, int hi, int a) {
  return clamp32(val, lo, hi);
}

struct func_info funcs[] = {
  // must match types-no-float-1204.lst
  /* 0 */  {"identity_fn", (func*)&identity_fn, 4, 0, 0},
  /* 1 */  {"identity_fn", (func*)&identity_fn, 4, 0, 0},
  /* 2 */  {"boost_clamp", (func*)&boost_clamp, 4, 0, 0}, // placeholder
  /* 3 */  {"ref1",         (func*)&ref1,       3, 0, 0},
  /* 4 */  {"ref2",         (func*)&ref2,       3, 0, 0},
  /* 5 */  {"ref3",         (func*)&ref3,       3, 0, 0},
  /* 6 */  {"ref4",         (func*)&ref4,       3, 0, 0},
  /* 7 */  {"ref5",         (func*)&ref5,       3, 0, 0},
  /* 8 */  {"ref6",         (func*)&ref6,       3, 0, 0},
  /* 9 */  {"ref7",         (func*)&ref7,       3, 0, 0},
  /* 10 */ {"ref8",         (func*)&ref8,       3, 0, 0},
  /* 11 */ {"ref9",         (func*)&ref9,       3, 0, 0},
  /* 12 */ {"ref10",        (func*)&ref10,      3, 0, 0},
  /* 13 */ {"ref11",        (func*)&ref11,      3, 0, 0},
  /* 14 */ {"ref12",        (func*)&ref12,      3, 0, 0},
  /* 15 */ {"ref13",        (func*)&ref13,    3, 0, 0},
  /* 16 */ {"ref14",        (func*)&ref14,    3, 0, 0},
  /* 17 */ {"ref15",        (func*)&ref15,    3, 0, 0},
  /* 18 */ {"ref16",        (func*)&ref16,    3, 0, 0},
  /* 19 */ {"ref17",        (func*)&ref17,    3, 0, 0},
  /* 20 */ {"ref18",        (func*)&ref18,    3, 0, 0},
  /* 21 */ {"ref19",        (func*)&ref19,    3, 0, 0},
  /* 22 */ {"ref20",        (func*)&ref20,    3, 0, 0},
  /* 23 */ {"ref21",        (func*)&ref21,    3, 0, 0},
  /* 24 */ {"ref22",        (func*)&ref22,    3, 0, 0},
  /* 25 */ {"ref23",        (func*)&ref23,    3, 0, 0},
  /* 26 */ {"ref24",        (func*)&ref24,    3, 0, 0},
  /* 27 */ {"ref25",        (func*)&ref25,    3, 0, 0},
};


int convert32to32s(int a) {
  int a1=(int) a;
  return (int) a1;
}

int convert32to32u(int a) {
  unsigned int a1=(int) a;
  return (unsigned int) a1;
}

int convert32to32(int a) {
  int a1=(int) a;
  a1 += 0x80000000;
  return a1;
}

int convert16to32s(int a) {
  short a1=(short) a;
  return (int) a1;
}

int convert16to32u(int a) {
  unsigned short a1=(short) a;
  return (unsigned int) a1;
}

int convert8to32s(int a) {
  char a1=(char) a;
  return (int) a1;
}

int convert8to32u(int a) {
  unsigned char a1=(char) a;
  return (unsigned int) a1;
}

int convert1to32s(int a) {
  char a1; 
  if( a & 1 ) a1=0xff; else a1=0;
  return (int) a1;
}

int convert1to32u(int a) {
  unsigned char a1=(char) a&1;
  return (unsigned int) a1;
}

int convert32to1(int a) { return (int) a != 0; }

