#include "cluster-adapters.h"
//#include "SignalHandlers.h"
//#include "generate_adapters.h"
//#include "calc_num_adapters.h"
#include <map>
#include <vector>
#include <assert.h>
#include <iostream>
#include "utils.h"

int adapter_family;

#if ADAPTER_FAMILY==2
#include "typeconv-utils.h"
#else
#include "arith-utils.h"
#endif
using namespace std;


argret ad;

void print_test(int ind) {
  printf("test(%d): (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)\n", ind,
	 tests[ind].a, tests[ind].b, tests[ind].c, tests[ind].d,
	 tests[ind].e, tests[ind].f, tests[ind].g, tests[ind].h,
	 tests[ind].i, tests[ind].j, tests[ind].k, tests[ind].l, tests[ind].m);
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
  if (adapter_family < 2 || adapter_family > 3) {
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
  //if (adapter_family == 3) num_adapters = num_arith_adapters;
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
	  //bool match = (adapter_family != 3) ?
	  //  compare(all_ads[i], all_ads[v[k]]) :
	  //  compare(all_arith_ads[i], all_arith_ads[v[k]]);
	  bool match = compare(all_ads[i], all_ads[v[k]]);
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
	// if (adapter_family != 3)
	//   print_adapter(all_ads[v[j]], fnargs);
	// else 
	//  print_adapter(all_arith_ads[v[j]], fnargs);
	print_adapter(all_ads[v[j]], fnargs);
	cout << endl;
      }
    }
  } else if (mode == 's') {
    int a0, a1, a2, a3, a4, a5, a6;
    while (fscanf(stdin, "%d %d %d %d", &a0, &a1, &a2, &a3) != EOF) {
      //if (adapter_family != 3) 
	printf("0x%x or %d\n", 
	       wrap_f(all_ads[adapter_ind], a0, a1, a2,
		      a3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
	       wrap_f(all_ads[adapter_ind], a0, a1, a2,
		      a3, 0, 0, 0, 0, 0, 0, 0, 0, 0));
	//else 
	// printf("0x%x or %d\n", 
	//        wrap_f(all_arith_ads[adapter_ind], a0, a1, a2,
	// 	      a3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
	//        wrap_f(all_arith_ads[adapter_ind], a0, a1, a2,
	// 	      a3, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    }
  }
 
  return 0;
}
