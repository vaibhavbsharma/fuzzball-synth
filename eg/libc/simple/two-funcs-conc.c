#include "two-funcs-conc.h"

#define MAX_ADAPTORS 100000
#define MAX_TESTS 100
int f1num, f2num;
int f1nargs=1, f2nargs=2;
bool void_flag=false;

typedef struct { int a,b,c,d,e,f} test; 
test tests[MAX_TESTS];
int num_tests=0;

void addTest(long a, long b, long c, long d, long e, long f) {
  tests[num_tests].a=a;
  tests[num_tests].b=b;
  tests[num_tests].c=c;
  tests[num_tests].d=d;
  tests[num_tests].e=e;
  tests[num_tests].f=f;
  num_tests++;
}
long f1(long a, long b, long c, long d, long e, long f) {
  return (funcs[f1num].fptr)(a, b, c, d, e, f);
}

long f2(long a, long b, long c, long d, long e, long f) {
  return (funcs[f2num].fptr)(a, b, c, d, e, f);
}

typedef struct {
  int var_is_const;
  int var_val;
} argsub;

typedef struct {
  int ret_type;
  int ret_val;
} retsub;

typedef struct {
  argsub a_ad[6];
  retsub r_ad;
} argret;

argret all_ads[MAX_ADAPTORS];
argret ad;
int num_adaptors=0;
int const_lb, const_ub;

void populateAdaptor() {
  int i;
  for(i=0;i<6; i++) 
    all_ads[num_adaptors].a_ad[i] = ad.a_ad[i];
  all_ads[num_adaptors].r_ad = ad.r_ad;
  num_adaptors++;
}

void generate_ret_adaptors() {
  int i,j;
  int f2arg_ret_type[8] = {11, 12, 21, 22, 31, 32, 41, 42};
  int retarg_ret_type[9] = {51, 52, 53, 61, 62, 71, 72, 81, 82};
  switch(0) {
  case 0: ad.r_ad.ret_type=0; populateAdaptor();
  case 1: ad.r_ad.ret_type=1;
    for(i=const_lb; i<= const_ub; i++) {
      ad.r_ad.ret_val=i;
      populateAdaptor(); 
    }
  case 11: case 12: case 21: case 22: case 31: case 32: case 41: case 42: 
    for(i=0; i<8; i++) {
      ad.r_ad.ret_type = f2arg_ret_type[i];
      for(j=0; j < f2nargs; j++) {
	ad.r_ad.ret_val = j;
	populateAdaptor();
      }
    }
  case 51: case 52: case 53: case 61: case 62: case 71: case 72: case 81: case 82:
    for(i=0; i<9; i++) {
      ad.r_ad.ret_type = retarg_ret_type[i];
      populateAdaptor();
    }
    break;
  }
}

// Sets up global list of randomly enumerated adaptors
// with total number in num_adaptors global
void generate_adaptors(int argnum) {
  int i, j;
  //each inner arg can be a constant
  //each inner arg can point to a target arg
  ad.a_ad[argnum].var_is_const=1;
  for(i=const_lb; i<=const_ub; i++) {
    ad.a_ad[argnum].var_val=i;
    if(argnum < f2nargs-1) 
      generate_adaptors(argnum+1);
    else generate_ret_adaptors(0);
  }
  
  ad.a_ad[argnum].var_is_const=0;
  for(i=0; i<f1nargs; i++) {
    bool found=false;
    for(j=0; j<argnum; j++) 
      if(ad.a_ad[j].var_is_const==0 && ad.a_ad[j].var_val==i) found=true; 
    if(!found) {
      ad.a_ad[argnum].var_val=i;
      if(argnum < f2nargs-1) 
	generate_adaptors(argnum+1);
      else generate_ret_adaptors(0);
    }
  }
}

void swap( int ind1, int ind2) {
  argret a;
  int i;
  for(i=0;i<6; i++) {
    a.a_ad[i] = all_ads[ind1].a_ad[i];
    all_ads[ind1].a_ad[i] = all_ads[ind2].a_ad[i];
    all_ads[ind2].a_ad[i] = a.a_ad[i];
  }
  a.r_ad = all_ads[ind1].r_ad;
  all_ads[ind1].r_ad = all_ads[ind2].r_ad;
  all_ads[ind2].r_ad=a.r_ad;
}

//http://www.geeksforgeeks.org/shuffle-a-given-array/
// A function to generate a random permutation of arr[]
void shuffle_adaptors() {
  int n = num_adaptors;
  int i,j;
  // Use a different seed value so that we don't get same
  // result each time we run this program
  srand ( time(NULL) );
 
  // Start from the last element and swap one by one. We don't
  // need to run for the first element that's why i > 0
  for (i = n-1; i > 0; i--)
    {
      // Pick a random index from 0 to i
      j = rand() % (i+1);
 
      // Swap all_ads[i] with the element at random index
      swap(i, j);
    }
}

void setup_adaptor(int index) {
  int i;
  for(i=0;i<6;i++) ad.a_ad[i]=all_ads[index].a_ad[i];
  ad.r_ad = all_ads[index].r_ad;
}

void print_adaptor(int index) {
  char output[200];
  printf("Input vars: ");
  int i;
  for(i=0; i<f2nargs; i++) {
    printf("%c_is_const=0x%x %c_val=0x%x ", 'a'+i, 
	   all_ads[index].a_ad[i].var_is_const, 'a'+i, all_ads[index].a_ad[i].var_val); 
  }
  printf("ret_type=0x%d ret_val=0x%d", all_ads[index].r_ad.ret_type, all_ads[index].r_ad.ret_val);
  printf("\n");
  fflush(stdout);
}

long convert32to64s(long a) {
  int a1=(int) a;
  return (long) a1;
}

long convert32to64u(long a) {
  unsigned int a1=(int) a;
  return (unsigned long) a1;
}

long convert16to64s(long a) {
  short a1=(short) a;
  return (long) a1;
}

long convert16to64u(long a) {
  unsigned short a1=(short) a;
  return (unsigned long) a1;
}

long convert8to64s(long a) {
  char a1=(char) a;
  return (long) a1;
}

long convert8to64u(long a) {
  unsigned char a1=(char) a;
  return (unsigned long) a1;
}

long convert1to64s(long a) {
  char a1; 
  if( a & 1 ) a1=0xff; else a1=1;
  return (long) a1;
}

long convert1to64u(long a) {
  unsigned char a1=(char) a&1;
  return (unsigned long) a1;
}

long convert64to1(long a) { return (long) a != 0; }

long wrap_f2(long a, long b, long c, long d, long e, long f) {
  long f1args[6]={a, b, c, d, e, f};
  long f2args[6];
  int i;
  for(i=0;i<6; i++) {
    if(ad.a_ad[i].var_is_const==1) f2args[i]=ad.a_ad[i].var_val;
    else f2args[i]=f1args[ad.a_ad[i].var_val];
  }
  long ret_val = f2(f2args[0], f2args[1], f2args[2], 
		    f2args[3], f2args[4], f2args[5]);
  switch(ad.r_ad.ret_type) {
  case 0: break;
  case 1: ret_val = ad.r_ad.ret_val;
  case 11: ret_val = convert32to64s(f2args[ad.r_ad.ret_val]);
  case 12: ret_val = convert32to64u(f2args[ad.r_ad.ret_val]);
  case 21: ret_val = convert16to64s(f2args[ad.r_ad.ret_val]);
  case 22: ret_val = convert16to64u(f2args[ad.r_ad.ret_val]);
  case 31: ret_val =  convert8to64s(f2args[ad.r_ad.ret_val]);
  case 32: ret_val =  convert8to64u(f2args[ad.r_ad.ret_val]);
  case 41: ret_val =  convert1to64s(f2args[ad.r_ad.ret_val]);
  case 42: ret_val =  convert1to64u(f2args[ad.r_ad.ret_val]);
  case 51: ret_val = convert32to64s(ret_val);
  case 52: ret_val = convert32to64u(ret_val);
  case 53: ret_val = convert64to1  (ret_val);
  case 61: ret_val = convert16to64s(ret_val);
  case 62: ret_val = convert16to64u(ret_val);
  case 71: ret_val =  convert8to64s(ret_val);
  case 72: ret_val =  convert8to64u(ret_val);
  case 81: ret_val =  convert1to64s(ret_val);
  case 82: ret_val =  convert1to64u(ret_val);
  default: break;
  }
  return ret_val;
}

int compare(long *r1p, long *r2p,
	    long a0, long a1, long a2, long a3, long a4, long a5) {
  int i, j;
  bool is_all_match;
  for(i=0;i<num_adaptors; i++) {
    bool is_match[MAX_TESTS];
    for(j=0; j<MAX_TESTS; j++) is_match[j]=false;
    for(j=0; j<num_tests; j++) {
      a0=tests[j].a;
      a1=tests[j].b;
      a2=tests[j].c;
      a3=tests[j].d;
      a4=tests[j].e;
      a5=tests[j].f;
      //printf("Starting f1\n");  
      //fflush(stdout);
      long r1, r2;
      r1 = f1(a0, a1, a2, a3, a4, a5);
      //printf("Completed f1\n");
      //fflush(stdout);
      //printf("Starting f2\n");
      //fflush(stdout);
      setup_adaptor(i);
      r2 = wrap_f2(a0, a1, a2, a3, a4, a5);
      //printf("Completed f2\n");
      //fflush(stdout);
      if (r1==r2) {
	//printf("Match\n");
	is_match[j]=true;
      } 
    }
    is_all_match=true;
    for(j=0;j<num_tests; j++) is_all_match = is_all_match & is_match[j];
    if(is_all_match) break;
  }
  if(is_all_match == 1) { 
    printf("All tests succeeded!\n");
    print_adaptor(i);
  }
  printf("is_all_match = %d\n", is_all_match);
  fflush(stdout);
  return is_all_match;
}

long global_arg0, global_arg1, global_arg2,
    global_arg3, global_arg4, global_arg5;

int main(int argc, char **argv) { 
  FILE *fh;
  if (argc == 9 && argv[3][0]=='f') {
    fh = fopen(argv[4], "r");
    const_lb = atoi(argv[5]);
    const_ub = atoi(argv[6]);
  }
  generate_adaptors(0);
  shuffle_adaptors();
  int i;
  //for(i=0;i<num_adaptors;i++) print_adaptor(i);
  if (argc < 4) {
    fprintf(stderr, "Usage: two-funcs <f1num> <f2num> a [0-6 args]\n");
    fprintf(stderr, "    or two-funcs <f1num> <f2num> g\n");
    fprintf(stderr, "    or two-funcs <f1num> <f2num> f <fname or -> <lower bound> <upper bound> <f1name> <f2name>\n");
    exit(1);
  }
  f1num = atoi(argv[1]);
  if (f1num < 0 || f1num >= sizeof(funcs)/sizeof(struct func_info)) {
    fprintf(stderr, "Error: f1num %d out of range\n", f1num);
  }
  f2num = atoi(argv[2]);
  if (f2num < 0 || f2num >= sizeof(funcs)/sizeof(struct func_info)) {
    fprintf(stderr, "Error: f2num %d out of range\n", f2num);
  }
  if((funcs[f1num].is_voidret==1) || (funcs[f2num].is_voidret==1) ) {
    void_flag=true;
  }
  f1nargs = funcs[f1num].num_args;
  f2nargs = funcs[f2num].num_args;
  if (argv[3][0] == 'a') {
    long args[6] = {0, 0, 0, 0, 0, 0};
    long r1, r2;
    int i;
    for (i = 0; i < 6 && i + 4 < argc; i++) {
      char *s = argv[i + 4];
      if (isdigit(s[0])) {
	args[i] = atol(s);
      } else {
	args[i] = (long)s;
      }
    }
    compare(&r1, &r2,
	    args[0], args[1], args[2], args[3], args[4], args[5]);
    if (r1 == r2) {
      printf("Both %ld\n", r1);
    } else {
      printf("Difference %ld vs. %ld\n", r1, r2);
    }
  } else if (argv[3][0] == 'g') {
    compare(0, 0,
	    global_arg0, global_arg1, global_arg2,
	    global_arg3, global_arg4, global_arg5);
  } else if (argv[3][0] == 'f') {
    long a, b, c, d, e, f;
    if (argv[4][0] == '-' && argv[4][1] == 0) {
      fh = stdin;
    } else {
      //fh = fopen(argv[4], "r");
      if (!fh) {
	fprintf(stderr, "Failed to open %s for reading: %s\n",
		argv[4], strerror(errno));
	return 1;
      }
    }
    while (fscanf(fh, "%lx %lx %lx %lx %lx %lx",
		  &a, &b, &c, &d, &e, &f) != EOF) {
      printf("read a test\n");
      fflush(stdout);
      addTest(a, b, c, d, e, f);
    }
    int is_eq = compare(0, 0, a, b, c, d, e, f);
    if (!is_eq)
      exit(1);
  } else {
    fprintf(stderr, "Unhandled command argument\n");
    exit(1);
  }
  return 0;
}
