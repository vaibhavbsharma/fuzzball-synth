//#include "all_adapters_clamp.h"
//#include "all_adapters_render.h"
//#include "all_adapters_absdiff.h"
//#include "all_adapters_bswap32.h"
//#include "all_adapters_tilepos.h"

#if ADAPTER_FAMILY==2
#if REFNUM==25
#include "typeconv/all_adapters_ref25.h"
#elif REFNUM==24
#include "typeconv/all_adapters_ref24.h"
#elif REFNUM==23
#include "typeconv/all_adapters_ref23.h"
#elif REFNUM==22
#include "typeconv/all_adapters_ref22.h"
#elif REFNUM==21
#include "typeconv/all_adapters_ref21.h"
#elif REFNUM==20
#include "typeconv/all_adapters_ref20.h"
#elif REFNUM==19
#include "typeconv/all_adapters_ref19.h"
#elif REFNUM==18
#include "typeconv/all_adapters_ref18.h"
#elif REFNUM==17
#include "typeconv/all_adapters_ref17.h"
#elif REFNUM==16
#include "typeconv/all_adapters_ref16.h"
#elif REFNUM==15
#include "typeconv/all_adapters_ref15.h"
#elif REFNUM==14
#include "typeconv/all_adapters_ref14.h"
#elif REFNUM==13
#include "typeconv/all_adapters_ref13.h"
#elif REFNUM==12
#include "typeconv/all_adapters_ref12.h"
#elif REFNUM==11
#include "typeconv/all_adapters_ref11.h"
#elif REFNUM==10
#include "typeconv/all_adapters_ref10.h"
#elif REFNUM==9
#include "typeconv/all_adapters_ref9.h"
#elif REFNUM==8
#include "typeconv/all_adapters_ref8.h"
#elif REFNUM==7
#include "typeconv/all_adapters_ref7.h"
#elif REFNUM==6
#include "typeconv/all_adapters_ref6.h"
#elif REFNUM==5
#include "typeconv/all_adapters_ref5.h"
#elif REFNUM==4
#include "typeconv/all_adapters_ref4.h"
#elif REFNUM==3
#include "typeconv/all_adapters_ref3.h"
#elif REFNUM==2
#include "typeconv/all_adapters_ref2.h"
#elif REFNUM==1
#include "typeconv/all_adapters_ref1.h"
#endif
#elif ADAPTER_FAMILY==3
#if REFNUM==25
#include "arithmetic/all_adapters_ref25.h"
#elif REFNUM==24
#include "arithmetic/all_adapters_ref24.h"
#elif REFNUM==23
#include "arithmetic/all_adapters_ref23.h"
#elif REFNUM==22
#include "arithmetic/all_adapters_ref22.h"
#elif REFNUM==21
#include "arithmetic/all_adapters_ref21.h"
#elif REFNUM==20
#include "arithmetic/all_adapters_ref20.h"
#elif REFNUM==19
#include "arithmetic/all_adapters_ref19.h"
#elif REFNUM==18
#include "arithmetic/all_adapters_ref18.h"
#elif REFNUM==17
#include "arithmetic/all_adapters_ref17.h"
#elif REFNUM==16
#include "arithmetic/all_adapters_ref16.h"
#elif REFNUM==15
#include "arithmetic/all_adapters_ref15.h"
#elif REFNUM==14
#include "arithmetic/all_adapters_ref14.h"
#elif REFNUM==13
#include "arithmetic/all_adapters_ref13.h"
#elif REFNUM==12
#include "arithmetic/all_adapters_ref12.h"
#elif REFNUM==11
#include "arithmetic/all_adapters_ref11.h"
#elif REFNUM==10
#include "arithmetic/all_adapters_ref10.h"
#elif REFNUM==9
#include "arithmetic/all_adapters_ref9.h"
#elif REFNUM==8
#include "arithmetic/all_adapters_ref8.h"
#elif REFNUM==7
#include "arithmetic/all_adapters_ref7.h"
#elif REFNUM==6
#include "arithmetic/all_adapters_ref6.h"
#elif REFNUM==5
#include "arithmetic/all_adapters_ref5.h"
#elif REFNUM==4
#include "arithmetic/all_adapters_ref4.h"
#elif REFNUM==3
#include "arithmetic/all_adapters_ref3.h"
#elif REFNUM==2
#include "arithmetic/all_adapters_ref2.h"
#elif REFNUM==1
#include "arithmetic/all_adapters_ref1.h"
#endif
#endif
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

