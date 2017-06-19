#include "adaptor_types.h"

bool generated_a_adaptors[6]={0,0,0,0,0,0};
arithsub a_ads[6][ARITH_PER_ARG_LIM];
int a_ads_ind_arr[6]={0,0,0,0,0,0};

extern int adaptor_family;
extern int f1nargs, f2nargs;
extern argret ad;
extern const_lb, const_ub;
extern unsigned long num_adaptors_g;
extern bool calculating;
extern unsigned long number_of_adaptors_tried;
extern bool find_all_correct_adaptors;
extern unsigned long number_of_correct_adaptors;
extern arithsub a_ad[6];
extern long f2 (long, long, long, long, long, long);

void swap_arithsub(arithsub *a1, arithsub *a2) {
  arithsub a;
  a.type_R = a1->type_R;
  a1->type_R = a2->type_R;
  a2->type_R = a.type_R;
  a.val_R = a1->val_R;
  a1->val_R = a2->val_R;
  a2->val_R = a.val_R;
  a.type_R0 = a1->type_R0;
  a1->type_R0 = a2->type_R0;
  a2->type_R0 = a.type_R0;
  a.val_R0 = a1->val_R0;
  a1->val_R0 = a2->val_R0;
  a2->val_R0 = a.val_R0;
  a.type_R1 = a1->type_R1;
  a1->type_R1 = a2->type_R1;
  a2->type_R1 = a.type_R1;
  a.val_R1 = a1->val_R1;
  a1->val_R1 = a2->val_R1;
  a2->val_R1 = a.val_R1;
}

void shuffle_adaptors_arithsub(arithsub *ads, int num_adaptors) {
  int n = num_adaptors;
  int i,j;
  srand ( time(NULL) );
  for (i = n-1; i > 0; i--) {
    j = rand() % (i+1);
    swap_arithsub(&ads[i], &ads[j]);
  }
}

char *get_a_adaptor_string(char *str, arithsub *a) {
  int len=0;
  int i;
  char type_varname[10];
  char val_varname[10];
  char my_str[ADAPTOR_STR_LEN/2];
  len+=sprintf(str, "Input vars: ");
  sprintf(type_varname, "_type_R");
  sprintf(val_varname, "_val_R");
  for(i=0; i<f2nargs; i++) {
    len+=sprintf(my_str, 
		 "%c%s=0x%x %c%s=0x%lx %c%s0=0x%x %c%s0=0x%lx %c%s1=0x%x %c%s1=0x%lx ", 
		 'a'+i, type_varname, a[i].type_R, 
		 'a'+i, val_varname, a[i].val_R,
		 'a'+i, type_varname, a[i].type_R0, 
		 'a'+i, val_varname, a[i].val_R0,
		 'a'+i, type_varname, a[i].type_R1, 
		 'a'+i, val_varname, a[i].val_R1); 
    sprintf(str, "%s%s", str, my_str);
  }
  assert(len<= ADAPTOR_STR_LEN);
  return str;
}

void print_a_adaptor() {
  char str[ADAPTOR_STR_LEN*6];
  printf("%s\n", get_a_adaptor_string(str, a_ad));
  fflush(stdout);
}

void generate_arithmetic_adaptors_randomized(int argnum) {
  int i, j, k, m;
  int ads_ind=0;
  assert(adaptor_family==3);
  //           +,-,&,|,^,<<,>>,>>a, -,!
  int ops[10]={0,1,2,3,4,5 ,6 ,7  , 8,9};
  if(!generated_a_adaptors[argnum]) {
    //each inner arg can be a constant
    for(i=const_lb; i<=const_ub; i++) {
      a_ads[argnum][ads_ind].type_R=0;
      a_ads[argnum][ads_ind++].val_R=i;
      assert(ads_ind <= ARITH_PER_ARG_LIM);
    }
    printf("ads_ind = %d\n", ads_ind);
    //points to target arg
    for(i=0; i<f1nargs; i++) {
      a_ads[argnum][ads_ind].type_R=1;
      a_ads[argnum][ads_ind++].val_R=i;
      assert(ads_ind <= ARITH_PER_ARG_LIM);
    }
    printf("ads_ind = %d\n", ads_ind);
    //const BINOP const
    for(i=0; i<=7; i++) {
      for(j=const_lb; j<=const_ub; j++) {
	for(k=const_lb; k<=const_ub; k++) { 
	  a_ads[argnum][ads_ind].type_R=2;
	  a_ads[argnum][ads_ind].val_R=ops[i];
	  a_ads[argnum][ads_ind].type_R0=0;
	  a_ads[argnum][ads_ind].type_R1=0;
	  a_ads[argnum][ads_ind].val_R0=j;
	  a_ads[argnum][ads_ind++].val_R1=k;
	  assert(ads_ind <= ARITH_PER_ARG_LIM);
	}
      }
    }
    printf("ads_ind = %d\n", ads_ind);
    //UNOP const
    for(i=8; i<=9; i++) {
      for(j=const_lb; j<=const_ub; j++) {
	a_ads[argnum][ads_ind].type_R=2;
	a_ads[argnum][ads_ind].val_R=ops[i];
	a_ads[argnum][ads_ind].type_R0=0;
	a_ads[argnum][ads_ind++].val_R0=j;
	assert(ads_ind <= ARITH_PER_ARG_LIM);
      }
    }
    printf("ads_ind = %d\n", ads_ind);
    //const BINOP f1arg
    for(i=0; i<=7; i++) {
      for(j=const_lb; j<=const_ub; j++) {
	for(k=0; k<f1nargs; k++) { 
	  a_ads[argnum][ads_ind].type_R=2;
	  a_ads[argnum][ads_ind].val_R=ops[i];
	  a_ads[argnum][ads_ind].type_R0=0;
	  a_ads[argnum][ads_ind].type_R1=1;
	  a_ads[argnum][ads_ind].val_R0=j;
	  a_ads[argnum][ads_ind++].val_R1=k;
	  assert(ads_ind <= ARITH_PER_ARG_LIM);
	}
      }
    } 
    printf("ads_ind = %d\n", ads_ind);
    //f1arg BINOP const
    for(i=0; i<=7; i++) {
      for(j=const_lb; j<=const_ub; j++) {
	for(k=0; k<f1nargs; k++) { 
	  a_ads[argnum][ads_ind].type_R=2;
	  a_ads[argnum][ads_ind].val_R=ops[i];
	  a_ads[argnum][ads_ind].type_R1=0;
	  a_ads[argnum][ads_ind].type_R0=1;
	  a_ads[argnum][ads_ind].val_R1=j;
	  a_ads[argnum][ads_ind++].val_R0=k;
	  assert(ads_ind <= ARITH_PER_ARG_LIM);
	}
      }
    }
    printf("ads_ind = %d\n", ads_ind);
    //UNOP f1arg
    for(i=8; i<=9; i++) {
      for(j=0; j<f1nargs; j++) {
	a_ads[argnum][ads_ind].type_R=2;
	a_ads[argnum][ads_ind].val_R=ops[i];
	a_ads[argnum][ads_ind].type_R0=1;
	a_ads[argnum][ads_ind++].val_R0=j;
	assert(ads_ind <= ARITH_PER_ARG_LIM);
      }
    }
    printf("ads_ind = %d\n", ads_ind);
    //f1arg BINOP f1arg
    for(i=0; i<=7; i++) {
      for(j=0; j<f1nargs; j++) {
	for(k=0; k<f1nargs; k++) {
	  a_ads[argnum][ads_ind].type_R=2;
	  a_ads[argnum][ads_ind].val_R=ops[i];
	  a_ads[argnum][ads_ind].type_R0=1;
	  a_ads[argnum][ads_ind].type_R1=1;
	  a_ads[argnum][ads_ind].val_R0=j;
	  a_ads[argnum][ads_ind++].val_R1=k;
	  assert(ads_ind <= ARITH_PER_ARG_LIM);
	}
      }
    }
 
    shuffle_adaptors_arithsub(a_ads[argnum], ads_ind);
    a_ads_ind_arr[argnum]=ads_ind;
    generated_a_adaptors[argnum]=true;
    if(calculating) {
      num_adaptors_g *= ads_ind;
      printf("argsub: ads_ind = %d\n", ads_ind);
    }
  }

  ads_ind = a_ads_ind_arr[argnum];
  for(i=0; i<ads_ind; i++) {
    a_ad[argnum].type_R=a_ads[argnum][i].type_R;
    a_ad[argnum].val_R=a_ads[argnum][i].val_R;
    a_ad[argnum].type_R0=a_ads[argnum][i].type_R0;
    a_ad[argnum].val_R0=a_ads[argnum][i].val_R0;
    a_ad[argnum].type_R1=a_ads[argnum][i].type_R1;
    a_ad[argnum].val_R1=a_ads[argnum][i].val_R1;
    if(argnum+1 < f2nargs) 
      generate_arithmetic_adaptors_randomized(argnum+1);
    else {
      number_of_adaptors_tried++;
      if(compare()) {
	if(!find_all_correct_adaptors) exit(0);
	else {
	  char str[ADAPTOR_STR_LEN];
	  printf("Number of adaptors tried = %ld\n", number_of_adaptors_tried);
	  printf("Correct adaptor %d = %s\n", number_of_correct_adaptors, get_a_adaptor_string(str, a_ad));
	  fflush(stdout);
	  number_of_correct_adaptors++;
	}
      }
    }
  }
}

// http://stackoverflow.com/questions/7622/are-the-shift-operators-arithmetic-or-logical-in-c
int logicalRightShift(int x, int n) {
  return (unsigned)x >> n;
}

int arithmeticRightShift(int x, int n) {
  if (x < 0 && n > 0)
    return x >> n | ~(~0U >> n);
  else
    return x >> n;
}

long getOp(arithsub ar, long *f1args, int operand) {
  int ret=0;
  switch(operand) {
  case 1:
    switch(ar.type_R0) {
    case 0: ret=ar.val_R0; break;
    case 1: ret=f1args[ar.val_R0]; break;
    case 2: default:
      ret=-1;
      char str[ADAPTOR_STR_LEN];
      printf("arithsub.type_R0 is neither 0 nor 1, panic!");
      break;
    }
    break;
  case 2:
    switch(ar.type_R1) {
    case 0: ret=ar.val_R1; break;
    case 1: ret=f1args[ar.val_R1]; break;
    case 2: default:
      ret=-1;
      char str[ADAPTOR_STR_LEN];
      printf("arithsub.type_R1 is neither 0 nor 1, panic!"); 
      break;
    }
    break;
  default: break;
  }
  return ret;
}

long wrap_a_f2(long a, long b, long c, long d, long e, long f) {
  long f1args[6]={a, b, c, d, e, f};
  long f2args[6];
  
  // char str[ADAPTOR_STR_LEN*6];
  // printf("trying adaptor: %s\n", get_a_adaptor_string(str, a_ad));
  // fflush(stdout);
  
  int i;
  for(i=0;i<6; i++) {
    switch(a_ad[i].type_R) {
    case 0: f2args[i]=a_ad[i].val_R; break;
    case 1: f2args[i]=f1args[a_ad[i].val_R] ; break;
    case 2: default: 
      switch(a_ad[i].val_R) {
      case 0: f2args[i] = getOp(a_ad[i], f1args, 1) + getOp(a_ad[i], f1args, 2);break; 
      case 1: f2args[i] = getOp(a_ad[i], f1args, 1) - getOp(a_ad[i], f1args, 2);break; 
      case 2: f2args[i] = getOp(a_ad[i], f1args, 1) & getOp(a_ad[i], f1args, 2);break; 
      case 3: f2args[i] = getOp(a_ad[i], f1args, 1) | getOp(a_ad[i], f1args, 2);break; 
      case 4: f2args[i] = getOp(a_ad[i], f1args, 1) ^ getOp(a_ad[i], f1args, 2);break; 
      case 5: f2args[i] = getOp(a_ad[i], f1args, 1) << getOp(a_ad[i], f1args, 2);break; 
      case 6: f2args[i] = logicalRightShift(getOp(a_ad[i], f1args, 1), getOp(a_ad[i], f1args, 2));
	break;
      case 7: f2args[i] = arithmeticRightShift(
					       getOp(a_ad[i], f1args, 1), 
					       getOp(a_ad[i], f1args, 2)); 
	break;
      case 8: f2args[i] = -getOp(a_ad[i], f1args, 1);
	break;
      case 9: f2args[i] = !getOp(a_ad[i], f1args, 1);
	break;
      default: break;
      }
      break;
    }
  }
  long ret_val = f2(f2args[0], f2args[1], f2args[2], 
		    f2args[3], f2args[4], f2args[5]);
  return ret_val;
}
