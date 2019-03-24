#include "cluster-adapters.h"
//#include "SignalHandlers.h"
//#include "generate_adapters.h"
//#include "calc_num_adapters.h"
#include <map>
#include <vector>
#include <assert.h>
#include <iostream>
#include "utils.h"
#include "arith-utils.h"
using namespace std;


argret ad;
int adapter_family = 2;

void print_test(int ind) {
  printf("test(%d): (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)\n", ind,
	 tests[ind].a, tests[ind].b, tests[ind].c, tests[ind].d,
	 tests[ind].e, tests[ind].f, tests[ind].g, tests[ind].h,
	 tests[ind].i, tests[ind].j, tests[ind].k, tests[ind].l, tests[ind].m);
}

void print_adapter(argret ad, int fnargs) {
  char output[200];
  //printf("Input vars: ");
  int i;
  char type_varname[10];
  char type_string[100];
  if(adapter_family==1) sprintf(type_varname,"_is_const");
  else if(adapter_family==2) sprintf(type_varname, "_type");
  else printf("undefined adapter_family\n");
  for(i=0; i<fnargs; i++) {
    switch(ad.a_ad[i].var_is_const) {
    case 1:  sprintf(type_string, "const("); break;
    case 0:  sprintf(type_string, "("); break;
    case 13: sprintf(type_string, "32-to-32C("); break;
    case 21: sprintf(type_string, "16-to-32S("); break;
    case 22: sprintf(type_string, "16-to-32Z("); break;
    case 31: sprintf(type_string, "8-to-32S("); break;
    case 32: sprintf(type_string, "8-to-32Z("); break;
    case 41: sprintf(type_string, "1-to-32S("); break;
    case 42: sprintf(type_string, "1-to-32Z("); break;
    default: sprintf(type_string, "32-to-1("); break;
    }
    sprintf(type_string, "%s0x%lx), ", type_string, ad.a_ad[i].var_val);
    printf("%s", type_string);
    // printf("%c%s=0x%x %c_val=0x%lx ", 'a'+i, type_varname,  
    // 	   ad.a_ad[i].var_is_const, 'a'+i, ad.a_ad[i].var_val); 
  }
  char r_type_string[100];
  switch(ad.r_ad.ret_type) {
  case 0:  sprintf(r_type_string, "("); break;
  case 53: sprintf(r_type_string, "32-to-1("); break;
  case 61: sprintf(r_type_string, "16-to-32S("); break;
  case 62: sprintf(r_type_string, "16-to-32Z("); break;
  case 71: sprintf(r_type_string, "8-to-32S("); break;
  case 72: sprintf(r_type_string, "8-to-32Z("); break;
  case 81: sprintf(r_type_string, "1-to-32S("); break;
  default: sprintf(r_type_string, "1-to-32Z("); break;
  }
  sprintf(r_type_string, "%s0x%lx)", r_type_string, ad.r_ad.ret_val);
  printf("and %s ", r_type_string);
  //printf("ret_type=0x%x ret_val=0x%lx", ad.r_ad.ret_type, ad.r_ad.ret_val);
  printf("\n");
  fflush(stdout);
}

int wrap_f(argret ad, int a, int b, int c, int d, int e, int f,
	     int g, int h, int _i, int j, int k, int l, int m) {
  int f1args[13]={a, b, c, d, e, f,g,h,_i,j,k,l,m};
  int f2args[13];
  
  // char str[ADAPTER_STR_LEN];
  // printf("trying adapter: %s\n", get_adapter_string(str, ad));
  // fflush(stdout);
  
  for(int i=0;i<13; i++) {
    switch(ad.a_ad[i].var_is_const) {
    case 1: f2args[i]=ad.a_ad[i].var_val; break;
    case 0: f2args[i]=f1args[ad.a_ad[i].var_val] ; break;
      //case 11: f2args[i] = convert32to32s(f1args[ad.a_ad[i].var_val]); break;
      //case 12: f2args[i] = convert32to32u(f1args[ad.a_ad[i].var_val]); break;
    case 13: f2args[i] = convert32to32(f1args[ad.a_ad[i].var_val]); break;
    case 21: f2args[i] = convert16to32s(f1args[ad.a_ad[i].var_val]); break;
    case 22: f2args[i] = convert16to32u(f1args[ad.a_ad[i].var_val]); break;
    case 31: f2args[i] =  convert8to32s(f1args[ad.a_ad[i].var_val]); break;
    case 32: f2args[i] =  convert8to32u(f1args[ad.a_ad[i].var_val]); break;
    case 41: f2args[i] =  convert1to32s(f1args[ad.a_ad[i].var_val]); break;
    case 42: f2args[i] =  convert1to32u(f1args[ad.a_ad[i].var_val]); break;
    default: f2args[i] =   convert32to1(f1args[ad.a_ad[i].var_val]); break;
    }
  }
  int ret_val = f1(f2args[0], f2args[1], f2args[2],
		    f2args[3], f2args[4], f2args[5],
		    f2args[6], f2args[7], f2args[8],
		    f2args[9], f2args[10], f2args[11],
		    f2args[12]);
  switch(ad.r_ad.ret_type) {
  case 0: break;
    // case 1: ret_val = ad.r_ad.ret_val; break;
    // case 11: ret_val = convert32to32s(f2args[ad.r_ad.ret_val]); break;
    // case 12: ret_val = convert32to32u(f2args[ad.r_ad.ret_val]); break;
    // case 21: ret_val = convert16to32s(f2args[ad.r_ad.ret_val]); break;
    // case 22: ret_val = convert16to32u(f2args[ad.r_ad.ret_val]); break;
    // case 31: ret_val =  convert8to32s(f2args[ad.r_ad.ret_val]); break;
    // case 32: ret_val =  convert8to32u(f2args[ad.r_ad.ret_val]); break;
    // case 41: ret_val =  convert1to32s(f2args[ad.r_ad.ret_val]); break;
    // case 42: ret_val =  convert1to32u(f2args[ad.r_ad.ret_val]); break;
    // case 51: ret_val = convert32to32s(ret_val); break;
    // case 52: ret_val = convert32to32u(ret_val); break;
  case 53: ret_val = convert32to1  (ret_val); break;
  case 61: ret_val = convert16to32s(ret_val); break;
  case 62: ret_val = convert16to32u(ret_val); break;
  case 71: ret_val =  convert8to32s(ret_val); break;
  case 72: ret_val =  convert8to32u(ret_val); break;
  case 81: ret_val =  convert1to32s(ret_val); break;
  default: ret_val =  convert1to32u(ret_val); break;
  }
  return ret_val;
}


bool compare(argret ad1, argret ad2) {
  int j, k;
  bool is_all_match = true;
  int a0, a1, a2, a3, a4, a5;
  int a6, a7, a8, a9, a10, a11, a12;
  for(j=0; j<MAX_TESTS; j++) {
    a0=tests[j].a;
    a1=tests[j].b;
    a2=tests[j].c;
    a3=tests[j].d;
    a4=tests[j].e;
    a5=tests[j].f;
    a6=tests[j].g;
    a7=tests[j].h;
    a8=tests[j].i;
    a9=tests[j].j;
    a10=tests[j].k;
    a11=tests[j].l;
    a12=tests[j].m;
    //printf("Starting f1, j=%d\n", j);  
    //fflush(stdout);
    int r1, r2;
    r1 = wrap_f(ad1, a0, a1, a2, a3, a4, a5,
		 a6, a7, a8, a9, a10, a11, a12);
    // printf("Completed f1\n");
    // fflush(stdout);
    // printf("Starting f2\n");
    // fflush(stdout);
    r2 = wrap_f(ad2, a0, a1, a2, a3, a4, a5,
		 a6, a7, a8, a9, a10, a11, a12);
    // printf("Completed f2\n");
    // fflush(stdout);
    if (r1==r2) {
      //printf("Match\n");
    } else {
      is_all_match = false;
      break; 
    }
  }
  return is_all_match;
}

void generate_tests() {
  srand(2);
  long range = 2*(0xfffff)-1;
  long bucket_size = range/MAX_TESTS;
  for(int i=0; i < MAX_TESTS; i++) {
    long bucket_start = i*bucket_size - 0xfffff;
    tests[i].a = (rand()%bucket_size) + bucket_start;
    tests[i].b = (rand()%bucket_size) + bucket_start;
    tests[i].c = (rand()%bucket_size) + bucket_start;
    tests[i].d = (rand()%bucket_size) + bucket_start;
    tests[i].e = (rand()%bucket_size) + bucket_start;
    tests[i].f = (rand()%bucket_size) + bucket_start;
    tests[i].g = (rand()%bucket_size) + bucket_start;
    tests[i].h = (rand()%bucket_size) + bucket_start;
    tests[i].i = (rand()%bucket_size) + bucket_start;
    tests[i].j = (rand()%bucket_size) + bucket_start;
    tests[i].k = (rand()%bucket_size) + bucket_start;
    tests[i].l = (rand()%bucket_size) + bucket_start;
    tests[i].m = (rand()%bucket_size) + bucket_start;
    //print_test(i);
  }
}

int main(int argc, char **argv) { 
  int numTests=0, adapter_ind = 0;
  generate_tests();
  FILE *fh;
  if (argc < 5) {
    fprintf(stderr, "Usage: cluster-adapters <adapter family (2=typeconv, 3=arithmetic-depth-2)> <c(luster) or s(ingle)> <fnum> <fnargs> <if s(ingle) then adapter num>\n");
    exit(1);
  }
  adapter_family = atoi(argv[1]);
  if (adapter_family < 1 || adapter_family > 3) {
    fprintf(stderr, "unsupported adapter family");
    exit(1);
  }
  char mode = argv[2][0];
  if(mode != 'c' && mode != 's') {
    fprintf(stderr, "Error: unsupported mode, 1st argument needs to be c or s\n");
    exit(1);
  }
  fnum = atoi(argv[3]);
  if (fnum < 0 || fnum >= sizeof(funcs)/sizeof(struct func_info)) {
    fprintf(stderr, "Error: fnum %d out of range\n", fnum);
    exit(1);
  }
  int fnargs = atoi(argv[4]);
  if(fnargs < 1 || fnargs > 10) { 
    fprintf(stderr, "Error: fnargs %d is not valid (has to be between 1 and 10)\n", fnum);
    exit(1);
  }
  if (adapter_family == 3) num_adapters = num_arith_adapters;
  if(mode == 's') {
    if(argc != 6) fprintf(stderr, "Error: adapter index unspecified\n");
    adapter_ind = atoi(argv[5]);
    if(adapter_ind >= num_adapters) {
      fprintf(stderr, "Error: invalid adapter index provided\n");
      exit(1);
    }
  }
  
  if(mode == 'c') {
    map<int, vector<int> > clusters;
    int cluster_ind=-1;
    for(int i=0; i< num_adapters; i++) {
      bool found_cluster = false;
      int found_cluster_ind = -1;
      for(int j=0; j<=cluster_ind; j++) {
	vector<int> v = clusters[j];
	found_cluster = true;
	for(int k=0; k < v.size(); k++) {
	  bool match = (adapter_family != 3) ?
	    compare(all_ads[i], all_ads[v[k]]) :
	    compare(all_arith_ads[i], all_arith_ads[v[j]]);
	  if(!match) {
	    found_cluster=false;
	    break;
	  } 
	}
	if(found_cluster) {
	  found_cluster_ind = j;
	  break;
	}
      }
      if(!found_cluster) {
	cluster_ind++;
	vector<int> v;
	clusters[cluster_ind] = v;
	clusters[cluster_ind].push_back(i);
      } else {
	clusters[found_cluster_ind].push_back(i);
      }
    }
    cout << "number of clusters = " << cluster_ind+1<<endl;
    for(int i=0; i <= cluster_ind; i++) {
      vector<int> v = clusters[i];
      cout << "Cluster "<< i << " ("<<v.size()<<") : " << endl;
      for(int j=0; j < v.size(); j++) {
	cout << v[j] <<": Input vars: ";
	if (adapter_family != 3)
	  print_adapter(all_ads[v[j]], fnargs);
	else 
	  print_adapter(all_arith_ads[v[j]], fnargs);
	cout << endl;
      }
    }
  } else if (mode == 's') {
    int a0, a1, a2, a3, a4, a5, a6;
    while (fscanf(stdin, "%d %d %d %d", &a0, &a1, &a2, &a3) != EOF) {
      if (adapter_family != 3) 
	printf("0x%x or %d\n", 
	       wrap_f(all_ads[adapter_ind], a0, a1, a2,
		      a3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
	       wrap_f(all_ads[adapter_ind], a0, a1, a2,
		      a3, 0, 0, 0, 0, 0, 0, 0, 0, 0));
      else 
	printf("0x%x or %d\n", 
	       wrap_f(all_arith_ads[adapter_ind], a0, a1, a2,
		      a3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
	       wrap_f(all_arith_ads[adapter_ind], a0, a1, a2,
		      a3, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    }
  }
 
  return 0;
}
