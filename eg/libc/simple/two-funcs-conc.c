#include "two-funcs-conc.h"
#include "SignalHandlers.h"
#include "generate_adaptors.h"
#include <assert.h>

#define REGION_LIMIT 2
#define SANE_ADDR 0x42420000
#define MAX_ADAPTORS 1000000
#define MAX_TESTS 100


#include  <setjmp.h>

jmp_buf  JumpBuffer;                    /* a jump buffer            */

int f1num, f2num;
int f1nargs=6, f2nargs=6;
bool void_flag=false;
bool calculating = true;
unsigned long num_adaptors_g = 1;

typedef struct { long a,b,c,d,e,f} test; 
test tests[MAX_TESTS];
int num_tests=0;

long sideEffectsEqual;

void sanitize(long a, long *aS, char *fname, int numTest) {
  int i;
  char *p;
  char newfname[100];
  sprintf(newfname, "%s_%d", fname, numTest);
  if((a&SANE_ADDR) == SANE_ADDR) {
    FILE *f = fopen(newfname, "r");
    if(f) {
      p = (char *) malloc(REGION_LIMIT);
      for(i=0; i<REGION_LIMIT; i++) p[i]=0;
      size_t count = fread(p, 1, REGION_LIMIT, f);
      // if(count<REGION_LIMIT) {
      // 	printf("Failed to read %d bytes from %s\n", REGION_LIMIT, fname);
      // 	free(aS);
      // 	*aS = a;
      // 	return;
      // }
      *aS = (long) p;
      fclose(f);
    } else { *aS = a; printf("failed to open %s\n", newfname); }
  } else { printf("%lx need not be sanitized\n", a); *aS = a; }
  fflush(stdout);
}

void addTest(long a, long b, long c, long d, long e, long f) {
  tests[num_tests].a=a;
  tests[num_tests].b=b;
  tests[num_tests].c=c;
  tests[num_tests].d=d;
  tests[num_tests].e=e;
  tests[num_tests].f=f;
  num_tests++;
}

bool isSaneAddr(long a) { return a > 4096; }

long f1(long a, long b, long c, long d, long e, long f) {
  //if((f1num == 663 || f1num == 664 || f1num == 707 || f1num == 1323) && !isSaneAddr(a)) {
  //  sideEffectsEqual=0;
  //  return -1;
  //}
  //if( (f1num == 707 || f1num == 1323) && (!isSaneAddr(b) || (b!=0)) ) {
  //  sideEffectsEqual=0;
  //  return -1;
  //} 
  return (funcs[f1num].fptr)(a, b, c, d, e, f);
}

long f2(long a, long b, long c, long d, long e, long f) {
  //if((f2num == 663 || f2num == 664 || f2num == 707 || f2num == 1323) && !isSaneAddr(a)) { 
  //  sideEffectsEqual=0;
  //  return -1;
  //} 
  //if( (f2num == 707 || f2num == 1323) && (!isSaneAddr(b) && (b!=0)) ) {
  //  sideEffectsEqual=0;
  //  return -1;
  //} 
  return (funcs[f2num].fptr)(a, b, c, d, e, f);
}

argret all_ads[MAX_ADAPTORS];
argret ad;
int num_adaptors=0;
int const_lb, const_ub;
int adaptor_family;

void populateAdaptor() {
  int i;
  for(i=0;i<6; i++) 
    all_ads[num_adaptors].a_ad[i] = ad.a_ad[i];
  all_ads[num_adaptors].r_ad = ad.r_ad;
  //print_adaptor(num_adaptors);
  num_adaptors++;
  assert(num_adaptors <= MAX_ADAPTORS);
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
  assert(adaptor_family==1);
  //each inner arg can be a constant
  //each inner arg can point to a target arg
  ad.a_ad[argnum].var_is_const=1;
  for(i=const_lb; i<=const_ub; i++) {
    ad.a_ad[argnum].var_val=i;
    if(argnum+1 < f2nargs) 
      generate_adaptors(argnum+1);
    else generate_ret_adaptors();
  }
  
  ad.a_ad[argnum].var_is_const=0;
  for(i=0; i<f1nargs; i++) {
    bool found=false;
    for(j=0; j<argnum; j++) 
      if(ad.a_ad[j].var_is_const==0 && ad.a_ad[j].var_val==i) found=true; 
    if(!found) {
      ad.a_ad[argnum].var_val=i;
      if(argnum+1 < f2nargs) 
	generate_adaptors(argnum+1);
      else generate_ret_adaptors();
    }
  }
}

void generate_typeconv_adaptors(int argnum) {
  int i, j, l;
  assert(adaptor_family==2);
  //each inner arg can be a constant
  //each inner arg can point to a target arg
  ad.a_ad[argnum].var_is_const=1;
  for(i=const_lb; i<=const_ub; i++) {
    ad.a_ad[argnum].var_val=i;
    if(argnum+1 < f2nargs) 
      generate_typeconv_adaptors(argnum+1);
    else generate_ret_adaptors();
  }
  
  ad.a_ad[argnum].var_is_const=0;
  for(i=0; i<f1nargs; i++) {
    bool found=false;
    for(j=0; j<argnum; j++) 
      if(ad.a_ad[j].var_is_const==0 && ad.a_ad[j].var_val==i) found=true; 
    if(!found) {
      ad.a_ad[argnum].var_val=i;
      if(argnum+1 < f2nargs) 
	generate_typeconv_adaptors(argnum+1);
      else generate_ret_adaptors();
    }
  }
  int typeconv_op[9] = {11, 12, 21, 22, 31, 32, 41, 42, 43};
  for(l=0; l<9; l++) {
    ad.a_ad[argnum].var_is_const=typeconv_op[l];
    for(i=0; i<f1nargs; i++) {
      bool found=false;
      for(j=0; j<argnum; j++) 
	if(ad.a_ad[j].var_is_const!=1 && ad.a_ad[j].var_val==i) found=true; 
      if(!found) {
	ad.a_ad[argnum].var_val=i;
	if(argnum+1 < f2nargs) 
	  generate_typeconv_adaptors(argnum+1);
	else generate_ret_adaptors();
      }
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

void print_adaptor() {
  char output[200];
  printf("Input vars: ");
  int i;
  char type_varname[10];
  if(adaptor_family==1) sprintf(type_varname,"_is_const");
  else if(adaptor_family==2) sprintf(type_varname, "_type");
  else printf("undefined adaptor_family\n");
  for(i=0; i<f2nargs; i++) {
    printf("%c%s=0x%x %c_val=0x%lx ", 'a'+i, type_varname,  
	   ad.a_ad[i].var_is_const, 'a'+i, ad.a_ad[i].var_val); 
  }
  printf("ret_type=0x%x ret_val=0x%lx", ad.r_ad.ret_type, ad.r_ad.ret_val);
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
  if( a & 1 ) a1=0xff; else a1=0;
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
  
  // char str[ADAPTOR_STR_LEN];
  // printf("trying adaptor: %s\n", get_adaptor_string(str, ad));
  // fflush(stdout);
  
  int i;
  for(i=0;i<6; i++) {
    switch(ad.a_ad[i].var_is_const) {
    case 1: f2args[i]=ad.a_ad[i].var_val; break;
    case 0: f2args[i]=f1args[ad.a_ad[i].var_val] ; break;
    case 11: f2args[i] = convert32to64s(f1args[ad.a_ad[i].var_val]); break;
    case 12: f2args[i] = convert32to64u(f1args[ad.a_ad[i].var_val]); break;
    case 21: f2args[i] = convert16to64s(f1args[ad.a_ad[i].var_val]); break;
    case 22: f2args[i] = convert16to64u(f1args[ad.a_ad[i].var_val]); break;
    case 31: f2args[i] =  convert8to64s(f1args[ad.a_ad[i].var_val]); break;
    case 32: f2args[i] =  convert8to64u(f1args[ad.a_ad[i].var_val]); break;
    case 41: f2args[i] =  convert1to64s(f1args[ad.a_ad[i].var_val]); break;
    case 42: f2args[i] =  convert1to64u(f1args[ad.a_ad[i].var_val]); break;
    case 43: f2args[i] =   convert64to1(f1args[ad.a_ad[i].var_val]); break;
    default: break;
    }
  }
  long ret_val = f2(f2args[0], f2args[1], f2args[2], 
		    f2args[3], f2args[4], f2args[5]);
  switch(ad.r_ad.ret_type) {
  case 0: break;
  case 1: ret_val = ad.r_ad.ret_val; break;
  case 11: ret_val = convert32to64s(f2args[ad.r_ad.ret_val]); break;
  case 12: ret_val = convert32to64u(f2args[ad.r_ad.ret_val]); break;
  case 21: ret_val = convert16to64s(f2args[ad.r_ad.ret_val]); break;
  case 22: ret_val = convert16to64u(f2args[ad.r_ad.ret_val]); break;
  case 31: ret_val =  convert8to64s(f2args[ad.r_ad.ret_val]); break;
  case 32: ret_val =  convert8to64u(f2args[ad.r_ad.ret_val]); break;
  case 41: ret_val =  convert1to64s(f2args[ad.r_ad.ret_val]); break;
  case 42: ret_val =  convert1to64u(f2args[ad.r_ad.ret_val]); break;
  case 51: ret_val = convert32to64s(ret_val); break;
  case 52: ret_val = convert32to64u(ret_val); break;
  case 53: ret_val = convert64to1  (ret_val); break;
  case 61: ret_val = convert16to64s(ret_val); break;
  case 62: ret_val = convert16to64u(ret_val); break;
  case 71: ret_val =  convert8to64s(ret_val); break;
  case 72: ret_val =  convert8to64u(ret_val); break;
  case 81: ret_val =  convert1to64s(ret_val); break;
  case 82: ret_val =  convert1to64u(ret_val); break;
  default: break;
  }
  return ret_val;
}

int compare() {
  int j, k;
  bool is_all_match;
  long a0, a1, a2, a3, a4, a5;
  bool is_match[MAX_TESTS];
  if(calculating) {
    printf("Number of adaptors = %ld\n", num_adaptors_g);
    calculating=false;
  }
  for(k=0; k<MAX_TESTS; k++) is_match[k]=false;
  for(j=0; j<num_tests; j++) {
    sideEffectsEqual=1;
    a0=tests[j].a;
    a1=tests[j].b;
    a2=tests[j].c;
    a3=tests[j].d;
    a4=tests[j].e;
    a5=tests[j].f;
    //printf("Starting f1, j=%d\n", j);  
    fflush(stdout);
    long r1, r2;
    if (sigsetjmp(JumpBuffer, 1) != 0) {     /* set a return mark   */
      printf("returning from longjmp, j=%d\n", j);
      fflush(stdout);
      is_match[j]=false;
      break;
      continue;
    } // else printf("setjmp setup\n");
    fflush(stdout);
    r1 = f1(a0, a1, a2, a3, a4, a5);
    // printf("Completed f1\n");
    // fflush(stdout);
    // printf("Starting f2\n");
    // fflush(stdout);
    r2 = wrap_f2(a0, a1, a2, a3, a4, a5);
    // printf("Completed f2\n");
    // fflush(stdout);
    if (r1==r2 && sideEffectsEqual) {
      printf("Match\n");
      is_match[j]=true;
    } else break; 
  }
  is_all_match=true;
  for(j=0;j<num_tests; j++) is_all_match = is_all_match & is_match[j];
  if(is_all_match == 1) { 
    printf("All tests succeeded!\n");
    fflush(stdout);
    print_adaptor();
    fflush(stdout);
  }
  return is_all_match;
}

long global_arg0, global_arg1, global_arg2,
    global_arg3, global_arg4, global_arg5;

int main(int argc, char **argv) { 
  struct sigaction sSigaction;
  /* Register the signal hander using the siginfo interface*/
  sSigaction.sa_sigaction = div0_signal_handler;
  sSigaction.sa_flags = SA_SIGINFO;
  /* mask all other signals */
  sigfillset(&sSigaction.sa_mask);
  int ret = sigaction(SIGFPE, &sSigaction, NULL);
  if(ret) {
    perror("ERROR, sigaction failed");
    exit(-1);
  }

  struct sigaction sSigaction1;
  /* Register the signal hander using the siginfo interface*/
  sSigaction1.sa_sigaction = segv_signal_handler;
  sSigaction1.sa_flags = SA_SIGINFO;
  /* mask all other signals */
  sigfillset(&sSigaction1.sa_mask);
  ret = sigaction(SIGSEGV, &sSigaction1, NULL);
  if(ret) {
    perror("ERROR, sigaction failed");
    exit(-1);
  }


  int numTests=0;
  FILE *fh;
  if (argc == 9 && argv[3][0]=='f') {
    fh = fopen(argv[4], "r");
    const_lb = atoi(argv[5]);
    const_ub = atoi(argv[6]);
    adaptor_family = atoi(argv[8]);
  }
  if (argc < 4) {
    fprintf(stderr, "Usage: two-funcs <f1num> <f2num> a [0-6 args]\n");
    fprintf(stderr, "    or two-funcs <f1num> <f2num> g\n");
    fprintf(stderr, "    or two-funcs <f1num> <f2num> f <fname or -> <lower bound> <upper bound> \n<sideEffectsEqual's address> <argsub=1, typeconv=2>");
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
  int i;
  if (argv[3][0] == 'f') {
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
      long aS, bS, cS, dS, eS, fS;
      sanitize(a, &aS, "str_arg1", numTests);
      //printf("0x%lx sanitized to 0x%lx, string = %s\n", a, aS, (char *)aS);
      sanitize(b, &bS, "str_arg2", numTests);
      sanitize(c, &cS, "str_arg3", numTests);
      sanitize(d, &dS, "str_arg4", numTests);
      sanitize(e, &eS, "str_arg5", numTests);
      sanitize(f, &fS, "str_arg6", numTests);
      addTest(aS, bS, cS, dS, eS, fS);
      numTests++;
    }
    if(adaptor_family==1)
      generate_adaptors_randomized(0);
    else if(adaptor_family==2)
      generate_typeconv_adaptors_randomized(0);
    else {
      printf("unknown adaptor family\n");
      exit(1);
    }
    //int is_eq = compare();
    //if (!is_eq)
    //  exit(1);
  } else {
    fprintf(stderr, "Unhandled command argument\n");
    exit(1);
  }
  return 0;
}
