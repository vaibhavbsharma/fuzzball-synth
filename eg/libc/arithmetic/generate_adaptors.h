#include "arithmetic_adaptor.h"
#include <assert.h>

extern int adaptor_family;
extern int f1nargs, f2nargs;
extern argret ad;
extern const_lb, const_ub;
extern unsigned long num_adaptors_g;
extern bool calculating;
extern unsigned long number_of_adaptors_tried;
extern bool find_all_correct_adaptors;
extern unsigned long number_of_correct_adaptors;

bool generated_adaptors[6]={0,0,0,0,0,0};
argsub ads[6][PER_ARG_LIM];
int ads_ind_arr[6]={0,0,0,0,0,0};

bool generated_t_adaptors[6]={0,0,0,0,0,0};
argsub t_ads[6][PER_ARG_LIM];
int t_ads_ind_arr[6]={0,0,0,0,0,0};

bool generated_ret_adaptors=false;
retsub ret_ads[PER_ARG_LIM];
int ret_ads_ind;

void swap_argsub(argsub *a1, argsub *a2) {
  argsub a;
  a.var_is_const = a1->var_is_const;
  a1->var_is_const = a2->var_is_const;
  a2->var_is_const = a.var_is_const;
  a.var_val = a1->var_val;
  a1->var_val = a2->var_val;
  a2->var_val = a.var_val;
}

void swap_retsub(retsub *a1, retsub *a2) {
  retsub a;
  a.ret_type = a1->ret_type;
  a1->ret_type = a2->ret_type;
  a2->ret_type = a.ret_type;
  a.ret_val = a1->ret_val;
  a1->ret_val = a2->ret_val;
  a2->ret_val = a.ret_val;
}

//http://www.geeksforgeeks.org/shuffle-a-given-array/
// A function to generate a random permutation of arr[]
void shuffle_adaptors_argsub(argsub *ads, int num_adaptors) {
  int n = num_adaptors;
  int i,j;
  srand ( time(NULL) );
  for (i = n-1; i > 0; i--) {
    j = rand() % (i+1);
    swap_argsub(&ads[i], &ads[j]);
  }
}

// A function to generate a random permutation of arr[]
void shuffle_adaptors_retsub(retsub *ads, int num_adaptors) {
  int n = num_adaptors;
  int i,j;
  srand ( time(NULL) );
  for (i = n-1; i > 0; i--) {
    j = rand() % (i+1);
    swap_retsub(&ads[i], &ads[j]);
  }
}

char *get_adaptor_string(char *str, argret a) {
  int len=0;
  int i;
  char type_varname[10];
  char my_str[ADAPTOR_STR_LEN/2];
  len+=sprintf(str, "Input vars: ");
  if(adaptor_family==1) sprintf(type_varname,"_is_const");
  else if(adaptor_family==2) sprintf(type_varname, "_type");
  else sprintf(type_varname, "_undefined\n");
  for(i=0; i<f2nargs; i++) {
    len+=sprintf(my_str, "%c%s=0x%x %c_val=0x%lx ", 'a'+i, type_varname,  
	   a.a_ad[i].var_is_const, 'a'+i, a.a_ad[i].var_val); 
    sprintf(str, "%s%s", str, my_str);
  }
  len+=sprintf(my_str, "ret_type=0x%x ret_val=0x%lx", a.r_ad.ret_type, a.r_ad.ret_val);
  sprintf(str, "%s%s", str, my_str); 
  assert(len<= ADAPTOR_STR_LEN);
  return str;
}

void generate_adaptors_randomized(int argnum) {
  int i, j, k, m;
  int ads_ind=0;
  assert(adaptor_family==1);
  if(!generated_adaptors[argnum]) {
    //each inner arg can be a constant
    for(i=const_lb; i<=const_ub; i++) {
      ads[argnum][ads_ind].var_is_const=1;
      ads[argnum][ads_ind++].var_val=i;
      assert(ads_ind <= PER_ARG_LIM);
    }
    
    //each inner arg can point to a target arg
    for(i=0; i<f1nargs; i++) {
      ads[argnum][ads_ind].var_is_const=0;
      ads[argnum][ads_ind++].var_val=i;
      assert(ads_ind <= PER_ARG_LIM);
    }
    shuffle_adaptors_argsub(ads[argnum], ads_ind);
    ads_ind_arr[argnum]=ads_ind;
    generated_adaptors[argnum]=true;
    if(calculating) {
      num_adaptors_g *= ads_ind;
      printf("argsub: ads_ind = %d\n", ads_ind);
    }
  }

  ads_ind = ads_ind_arr[argnum];
  for(i=0; i<ads_ind; i++) {
    if(ads[argnum][i].var_is_const != 1) {
      bool found=false;
      for(j=0; j<argnum; j++) 
	if(ad.a_ad[j].var_is_const!=1 && 
	   ad.a_ad[j].var_val==ads[argnum][i].var_val) found=true;
      if(found) {
	//Find an non-conflicting adaptor after ads[argnum][i]
	for(j=i+1; j<ads_ind; j++) {
	  if(ads[argnum][j].var_is_const==1) break;
	  bool found1=false;
	  for(k=0; k<argnum; k++) 
	    if(ad.a_ad[k].var_is_const!=1 && 
	       ad.a_ad[k].var_val==ads[argnum][j].var_val) found1=true;
	  if(!found1) break;
	}
	if(j >= ads_ind) {
	  char str[ADAPTOR_STR_LEN];
	  printf("argnum=%d ran out of adaptors to try out, ad=%s\n", argnum, get_adaptor_string(str, ad));
	  return;
	}
	//Swap ads[argnum][j] with ads[argnum][i]
	swap_argsub(&ads[argnum][j], &ads[argnum][i]);
      }
    }
    ad.a_ad[argnum].var_is_const=ads[argnum][i].var_is_const;
    ad.a_ad[argnum].var_val=ads[argnum][i].var_val;
    if(argnum+1 < f2nargs) 
      generate_adaptors_randomized(argnum+1);
    else generate_ret_adaptors_randomized();
  }
}

void generate_ret_adaptors_randomized() {
  int i,j;
  int f2arg_ret_type[8] = {11, 12, 21, 22, 31, 32, 41, 42};
  int retarg_ret_type[9] = {51, 52, 53, 61, 62, 71, 72, 81, 82};
  int ads_ind=0;
  if(!generated_ret_adaptors) {
    ret_ads[ads_ind++].ret_type=0; 
    //populateAdaptor();
    for(i=const_lb; i<= const_ub; i++) {
      ret_ads[ads_ind].ret_type=1;
      ret_ads[ads_ind++].ret_val=i;
      assert(ads_ind <= PER_ARG_LIM);
    //populateAdaptor(); 
    }
    for(i=0; i<8; i++) {
      for(j=0; j < f2nargs; j++) {
	ret_ads[ads_ind].ret_type = f2arg_ret_type[i];
	ret_ads[ads_ind++].ret_val = j;
	assert(ads_ind <= PER_ARG_LIM);
	//populateAdaptor();
      }
    }
    for(i=0; i<9; i++) {
      ret_ads[ads_ind++].ret_type = retarg_ret_type[i];
      assert(ads_ind <= PER_ARG_LIM);
      //populateAdaptor();
    }
    shuffle_adaptors_retsub(ret_ads, ads_ind);
    if(calculating) {
      num_adaptors_g *= ads_ind;
      printf("ret: ads_ind = %d\n", ads_ind);
    }
    ret_ads_ind=ads_ind;
    generated_ret_adaptors=true;
  } 

  for(i=0; i<ret_ads_ind; i++) {
    ad.r_ad.ret_type=ret_ads[i].ret_type;
    ad.r_ad.ret_val=ret_ads[i].ret_val;
    number_of_adaptors_tried++;
    if(compare()) {
      if(!find_all_correct_adaptors) exit(0);
      else {
	char str[ADAPTOR_STR_LEN];
	printf("Number of adaptors tried = %ld\n", number_of_adaptors_tried);
	printf("Correct adaptor %d = %s\n", number_of_correct_adaptors, get_adaptor_string(str, ad));
	fflush(stdout);
	print_adaptor();
	fflush(stdout);
	number_of_correct_adaptors++;
      }
    }
  }
}

void generate_typeconv_adaptors_randomized(int argnum) {
  int i, j, l, k, m;
  assert(adaptor_family==2);
  int ads_ind=0;
  if(!generated_t_adaptors[argnum]) {
    for(i=const_lb; i<=const_ub; i++) {
      t_ads[argnum][ads_ind].var_is_const=1;
      t_ads[argnum][ads_ind++].var_val=i;
      assert(ads_ind <= PER_ARG_LIM);
    }
    for(i=0; i<f1nargs; i++) {
      t_ads[argnum][ads_ind].var_is_const=0;
      t_ads[argnum][ads_ind++].var_val=i;
      assert(ads_ind <= PER_ARG_LIM);
    }
    int typeconv_op[9] = {11, 12, 21, 22, 31, 32, 41, 42, 43};
    for(l=0; l<9; l++) {
      for(i=0; i<f1nargs; i++) {
	t_ads[argnum][ads_ind].var_is_const=typeconv_op[l];
	t_ads[argnum][ads_ind++].var_val=i;
	assert(ads_ind <= PER_ARG_LIM);
      }
    }
    shuffle_adaptors_argsub(t_ads[argnum], ads_ind);
    if(calculating) {
      num_adaptors_g *= ads_ind;
      printf("typeconv: ads_ind = %d\n", ads_ind);
    }
    generated_t_adaptors[argnum]=false;
    t_ads_ind_arr[argnum]=ads_ind;
  }

  for(i=0; i<t_ads_ind_arr[argnum]; i++) {
    if(t_ads[argnum][i].var_is_const != 1) {
      bool found=false;
      for(j=0; j<argnum; j++) 
	if(ad.a_ad[j].var_is_const!=1 && 
	   ad.a_ad[j].var_val==t_ads[argnum][i].var_val) found=true;
      if(found) {
	//Find an non-conflicting adaptor after t_ads[argnum][i]
	for(j=i+1; j<ads_ind; j++) {
	  if(t_ads[argnum][j].var_is_const==1) break;
	  bool found1=false;
	  for(k=0; k<argnum; k++) 
	    if(ad.a_ad[k].var_is_const!=1 && 
	       ad.a_ad[k].var_val==t_ads[argnum][j].var_val) found1=true;
	  if(!found1) break;
	}
	if(j >= ads_ind) {
	  char str[ADAPTOR_STR_LEN];
	  printf("argnum=%d ran out of adaptors to try out, ad=%s\n", argnum, get_adaptor_string(str, ad));
	  return;
	}
	//Swap t_ads[argnum][j] with t_ads[argnum][i]
	swap_argsub(&t_ads[argnum][j], &t_ads[argnum][i]);
      }
    }
    ad.a_ad[argnum].var_is_const=t_ads[argnum][i].var_is_const;
    ad.a_ad[argnum].var_val=t_ads[argnum][i].var_val;
    if(argnum+1 < f2nargs) 
      generate_typeconv_adaptors_randomized(argnum+1);
    else generate_ret_adaptors_randomized();
  }

}
