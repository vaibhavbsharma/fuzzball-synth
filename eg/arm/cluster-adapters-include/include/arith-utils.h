char *print_arith_node (int var_type, int var_val,
			char *type_string) {
  switch(var_type) {
  case 0:
    sprintf(type_string, "const(0x%x)", var_val);
    break;
  case 1:
    sprintf(type_string, "arg(0x%x)", var_val);
    break;
  case 2:
  default: printf("illegal var_type value (%d)", var_type); assert(false);
    }
  return type_string;
}

char *print_arithd2 (arithd2 ad,
			char *type_string) {
  switch(ad.this_var_type) {
    case 0:
      sprintf(type_string, "const(0x%lx)", ad.this_var_val);
      break;
    case 1:
      sprintf(type_string, "arg(0x%lx)", ad.this_var_val);
      break;
    case 2:
      char lstr[100], rstr[100];
      sprintf(type_string, "(%s, %s, %s)",
	      (ad.this_var_val == 0 ? "PLUS" : "MINUS"),
	      print_arith_node(ad.left_var_type, ad.left_var_val, lstr),
	      print_arith_node(ad.right_var_type, ad.right_var_val, rstr));
      break; 
    default: printf("illegal this_var_type value (%d)", ad.this_var_type); assert(false);
    }
  return type_string;
}



void print_adapter(arithd2ret ad, int fnargs) {
  char output[200];
  //printf("Input vars: ");
  int i;
  char type_varname[10];
  sprintf(type_varname, "_type");
  for(i=0; i<fnargs; i++) {
    char type_string[100];
    print_arithd2(ad.arith[i], type_string);
    printf("%s ", type_string);
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

int get_arith_node(int f1args[], int var_type, int var_val) {
  switch(var_type) {
  case 0: return var_val;
  case 1: return f1args[var_val];
  case 2:
  default: printf("illegal var_type value (%d)", var_type); assert(false);
  }
}

int get_arithd2(int f1args[], arithd2 arith) {
  switch(arith.this_var_type) {
  case 0: return arith.this_var_val;
  case 1: return f1args[arith.this_var_val];
  case 2:
    int left_arg = get_arith_node(f1args, arith.left_var_type, arith.left_var_val);
    int right_arg = get_arith_node(f1args, arith.right_var_type, arith.right_var_val);
    return (arith.this_var_val == 0 ? left_arg + right_arg : left_arg - right_arg);
  }
}

int wrap_f(arithd2ret ad, int a, int b, int c, int d, int e, int f,
	   int g, int h, int _i, int j, int k, int l, int m) {
  int f1args[13]={a, b, c, d, e, f,g,h,_i,j,k,l,m};
  int f2args[13];
  
  // char str[ADAPTER_STR_LEN];
  // printf("trying adapter: %s\n", get_adapter_string(str, ad));
  // fflush(stdout);
  
  for(int i=0;i<13; i++) {
    switch(ad.arith[i].this_var_type) {
    case 0: f2args[i]=ad.arith[i].this_var_val; break;
    case 1: f2args[i]=f1args[ad.arith[i].this_var_val] ; break;
    case 2: f2args[i] = get_arithd2(f1args, ad.arith[i]); break;
    default: printf("illegal var_type value (%d)", ad.arith[i].this_var_type); assert(false);
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


bool compare(arithd2ret ad1, arithd2ret ad2) {
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

