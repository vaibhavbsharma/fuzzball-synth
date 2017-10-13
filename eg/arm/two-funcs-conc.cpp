#include "two-funcs-conc.h"
//#include "SignalHandlers.h"
//#include "generate_adapters.h"
//#include "calc_num_adapters.h"
#include <map>
#include <vector>
#include <assert.h>
#include <iostream>
using namespace std;

#define MAX_ADAPTERS 1000000
#define MAX_TESTS 1000

int fnum;

typedef struct { int a,b,c,d,e,f,g,h,i,j,k,l,m; } test; 
test tests[MAX_TESTS];

int f1(int a, int b, int c, int d, int e, int f,
	int g, int h, int i, int j, int k, int l, int m) {
  return (funcs[fnum].fptr)(a, b, c, d, e, f,g,h,i,j,k,l,m);
}

argret ad;
int adapter_family = 2;

void populateAdapter() {
  int i;
  for(i=0;i<13; i++) 
    all_ads[num_adapters].a_ad[i] = ad.a_ad[i];
  all_ads[num_adapters].r_ad = ad.r_ad;
  //print_adapter(num_adapters);
  num_adapters++;
  assert(num_adapters <= MAX_ADAPTERS);
}

void print_adapter(argret ad, int fnargs) {
  char output[200];
  printf("Input vars: ");
  int i;
  char type_varname[10];
  char type_string[100];
  if(adapter_family==1) sprintf(type_varname,"_is_const");
  else if(adapter_family==2) sprintf(type_varname, "_type");
  else printf("undefined adapter_family\n");
  for(i=0; i<fnargs; i++) {
    switch(ad.a_ad[i].var_is_const) {
    case 1: sprintf(type_string, "const("); break;
    case 0: 
    case 11:
    case 12: sprintf(type_string, "("); break;
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
  for(int i=0; i < MAX_TESTS; i++) {
    tests[i].a = rand();
    tests[i].b = rand();
    tests[i].c = rand();
    tests[i].d = rand();
    tests[i].e = rand();
    tests[i].f = rand();
    tests[i].g = rand();
    tests[i].h = rand();
    tests[i].i = rand();
    tests[i].j = rand();
    tests[i].k = rand();
    tests[i].l = rand();
    tests[i].m = rand();
  }
}

int main(int argc, char **argv) { 
  int numTests=0;
  generate_tests();
  FILE *fh;
  if (argc < 3) {
    fprintf(stderr, "Usage: two-funcs-conc <fnum>\n");
    exit(1);
  }
  fnum = atoi(argv[1]);
  if (fnum < 0 || fnum >= sizeof(funcs)/sizeof(struct func_info)) {
    fprintf(stderr, "Error: fnum %d out of range\n", fnum);
  }
  int fnargs = atoi(argv[2]);
  if(fnargs < 1 || fnargs > 10) { 
    fprintf(stderr, "Error: fnargs %d is not valid (has to be between 1 and 10)\n", fnum);
  }
  
  // argret all_ads[2] = { 
  //   {
  //     {
  // 	{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} 
  //     }, 
  //    {0,0} 
  //   }, 
  //   {
  //     {
  // 	{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} 
  //     }, 
  //    {0,0} 
  //   }
  // };

  // for(int i=0; i < num_adapters; i++) {
  //   print_adapter(all_ads[i], fnargs);
  // }
 
  map<int, vector<int> > clusters;
  int cluster_ind=-1;
  for(int i=0; i< num_adapters; i++) {
    bool found_cluster = false;
    int found_cluster_ind = -1;
    for(int j=0; j<=cluster_ind; j++) {
      vector<int> v = clusters[j];
      found_cluster = true;
      for(int k=0; k < v.size(); k++) {
	if(!compare(all_ads[i], all_ads[v[k]])) {
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
  cout << "number of clusters = " << cluster_ind<<endl;
  for(int i=0; i <= cluster_ind; i++) {
    vector<int> v = clusters[i];
    cout << "Cluster "<< i << " ("<<v.size()<<") : " << endl;
    for(int j=0; j < v.size(); j++) {
      print_adapter(all_ads[v[j]], fnargs);
      cout << endl;
    }
  }
 
  return 0;
}
