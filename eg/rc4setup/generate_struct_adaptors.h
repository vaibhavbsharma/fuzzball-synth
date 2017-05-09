#include "adaptor_types.h"
#include <assert.h>

#define STRUCT_PER_F_LIM 1000
#define MAX_FIELDS 4
#define MAX_STEPS 1000
bool generated_struct_adaptors=false;
fieldsub f_ads[MAX_FIELDS][STRUCT_PER_F_LIM];
int f_ads_ind;

extern unsigned long region_limit;
extern unsigned int number_of_fields;
extern fieldsub m[MAX_FIELDS];

extern int adaptor_family;
extern bool calculating;
extern unsigned long number_of_adaptors_tried;
extern bool find_all_correct_adaptors;
extern unsigned long number_of_correct_adaptors;
extern unsigned long num_adaptors_g;

extern argret ad;

unsigned long sane_addrs[MAX_STEPS];
unsigned int sane_addrs_ind=0;
void add_sane_struct_addr(unsigned long p) {
  assert(sane_addrs_ind < MAX_STEPS);
  sane_addrs[sane_addrs_ind++]=p;
}


bool is_sane_struct_addr(unsigned long a) {
  int i;
  for(i=0;i<sane_addrs_ind;i++) 
    if(sane_addrs[i]==a) return true;
  return false;
  //return ((a - 0x42420000)/region_limit) < MAX_STEPS;
}

char *get_struct_adaptor_string(char *str, fieldsub *m) {
  assert(adaptor_family==4 || adaptor_family==14);
  int len=0;
  int i;
  char type_varname[10];
  char my_str[ADAPTOR_STR_LEN]={'\0'};
  str[0]='\0';
  for(i=0; i<number_of_fields; i++) {
    sprintf(my_str, "f%c_type=0x%lx f%c_size=0x%x f%c_n=0x%x ", '1'+i,   
		 m[i].type, '1'+i, m[i].size, '1'+i, m[i].n); 
    len = sprintf(str, "%s%s", str, my_str);
    str[len]='\0';
  }
  assert(len<= ADAPTOR_STR_LEN);
  return str;
}

void swap_fieldsub(fieldsub *a1, fieldsub *a2) {
  fieldsub a;
  a.type = a1->type;
  a1->type = a2->type;
  a2->type = a.type;
  a.n = a1->n;
  a1->n = a2->n;
  a2->n = a.n;
  a.size = a1->size;
  a1->size = a2->size;
  a2->size = a.size;
}

void shuffle_adaptors_fieldsub(fieldsub *ads, int num_adaptors) {
  int n = num_adaptors;
  int i,j;
  srand ( time(NULL) );
  for (i = n-1; i > 0; i--) {
    j = rand() % (i+1);
    swap_fieldsub(&ads[i], &ads[j]);
  }
}

bool is_pow_2(unsigned int a) {
  switch(a) {
  case 1: case 2: case 4: case 8: case 16: case 32: case 64: case 128: case 256:
  case 512: case 1024: return true;
  default: return false;
  }
  return false;
}

void populate_f(int fnum, int s, int e, int n, int z, int sign_ex) {
  f_ads[fnum][f_ads_ind].type = (s<<32) + (e << 16) + sign_ex;
  f_ads[fnum][f_ads_ind].size = z;
  f_ads[fnum][f_ads_ind].n = n;
}

void populate2(int s1, int e1, int n1, int z1, int s2, int e2, int n2, int z2) {
  populate_f(0, s1, e1, n1, z1, 0);
  populate_f(1, s1, e1, n1, z1, 0);
  populate_f(0, s1, e1, n1, z1, 1);
  populate_f(1, s1, e1, n1, z1, 1);
  f_ads_ind++;
}

void generate_struct_adaptors_randomized_old(int fieldnum) {
  int i, j, k;
  unsigned int s1,s2,s3,s4,s5,s6;
  unsigned int e1,e2,e3,e4,e5,e6;
  unsigned int n1,n2,n3,n4,n5,n6;
  unsigned int z1,z2,z3,z4,z5,z6;
  unsigned int b1,b2,b3,b4,b5,b6;
  assert(adaptor_family==4);
  if(!generated_struct_adaptors) {
    switch(number_of_fields) {
    case 2:
      s1=0;
      for(e1=region_limit-2; e1 >= s1; e1--) {
	s2=e1+1;
	b1=e1-s1+1;
	z1=1;
	n1 = b1;
	if(!is_pow_2(n1)) continue;
	for(e2=region_limit-1; e2 >= s2; e2--) {
	  b2 = e2 - s2 + 1;
	  z2=1;
	  n2 = b2;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=2;
	  n2 = b2/2;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=4;
	  n2 = b2/4;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=8;
	  n2 = b2/8;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	}
	z1=2;
	n1 = b1/2;
	if(!is_pow_2(n1)) continue;
	for(e2=region_limit-1; e2 >= s2; e2--) {
	  b2 = e2 - s2 + 1;
	  z2=1;
	  n2 = b2;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=2;
	  n2 = b2/2;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=4;
	  n2 = b2/4;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=8;
	  n2 = b2/8;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	}

	z1=4;
	n1 = b1/4;
	if(!is_pow_2(n1)) continue;
	for(e2=region_limit-1; e2 >= s2; e2--) {
	  b2 = e2 - s2 + 1;
	  z2=1;
	  n2 = b2;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=2;
	  n2 = b2/2;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=4;
	  n2 = b2/4;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=8;
	  n2 = b2/8;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	}

	z1=8;
	n1 = b1/8;
	if(!is_pow_2(n1)) continue;
	for(e2=region_limit-1; e2 >= s2; e2--) {
	  b2 = e2 - s2 + 1;
	  z2=1;
	  n2 = b2;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=2;
	  n2 = b2/2;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=4;
	  n2 = b2/4;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	  z2=8;
	  n2 = b2/8;
	  if(!is_pow_2(n2)) continue;
	  populate2(s1,e1,n1,z1, s2,e2,n2,z2);
	}

      }
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    default: printf("unsupported number of fields (%d)\n", number_of_fields);
      assert(0);
    }
    
    generated_struct_adaptors=true;
    //shuffle_adaptors_struct(ads[argnum], ads_ind);
    if(calculating) {
      num_adaptors_g *= f_ads_ind;
      printf("memsub: f_ads_ind = %d\n", f_ads_ind);
    }
  }

  
  for(i=0; i<f_ads_ind; i++) {
    for(j=0; j<number_of_fields; j++) {
      m[j].type=f_ads[j][i].type;
      m[j].size=f_ads[j][i].size;
      m[j].n=f_ads[j][i].n;
    }
    generate_ret_adaptors_randomized();
  }
}

// http://forum.codecall.net/topic/64715-how-to-generate-all-permutations/
/* arr is the string, curr is the current index to start permutation from and size is sizeof the arr */
void permutation(fieldsub *arr, int curr, int size)
{
  int i;
  if(curr == size-1) {
    generate_ret_adaptors_randomized();
  }
  else {
    for(i=curr; i<size; i++) {
      swap_fieldsub(&arr[curr], &arr[i]);
      permutation(arr, curr+1, size);
      swap_fieldsub(&arr[curr], &arr[i]);
    }
  }
}


void generate_struct_adaptors_randomized(long start, int fieldnum) {
 
  // m[0].type = 0x70001;
  // m[0].size = 4;
  // m[0].n = 2;
  // m[1].type = 0x800090001;
  // m[1].size = 4;
  // m[1].n = 2;
  // ad.r_ad.ret_type=0;
  // compare();
  
  fieldsub m_ads[PER_ARG_LIM];
  int m_ads_ind=0;
  int i, j, k, end;
  if(start >= region_limit && fieldnum < number_of_fields-1) return;

  int prev_end = 0;
  int prev_field_ind=0;
  if(fieldnum > 0) {
    for(prev_field_ind = 0; prev_field_ind < fieldnum; prev_field_ind++) 
      prev_end += m[prev_field_ind].n * m[prev_field_ind].size;
  }
  int bytes_remaining = (region_limit - prev_end - (number_of_fields-1-fieldnum));


  if(fieldnum == number_of_fields) {
    //f2's field layout could be a permutation as f1's field layout
    permutation(m, 0, number_of_fields);
    //generate_ret_adaptors_randomized();
    return;
  }
  for(end=start; end<=region_limit-(number_of_fields-1-fieldnum)-1; end++) {
    int n, sz; 
    long start1;
    
    sz=1;
    n = end - start + 1;
    if(is_pow_2(n)) {
      if(n*sz <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start<<32) + (end << 16);
	m_ads[m_ads_ind].size = sz;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = sz;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      //f2's field layout could be a widening permutation of f1's field layout
      if(n*2*sz <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start<<32) + (end << 16);
	m_ads[m_ads_ind].size = sz*2;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = sz*2;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      if(n*4*sz <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start<<32) + (end << 16);
	m_ads[m_ads_ind].size = sz*4;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = sz*4;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      if(n*8*sz <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start<<32) + (end << 16);
	m_ads[m_ads_ind].size = sz*8;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = sz*8;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
    }
    
    sz=2;
    start1=start;
    if(start%2 != 0) start1++;
    n = (end - start1 + 1)/2;
    if(is_pow_2(n) && (end-start1+1)%2 == 0) {
      if(n*sz <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = sz;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = sz;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      // narrowing
      if(n*(sz-1) <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = sz-1;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = sz-1;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      //f2's field layout could be a widening permutation of f1's field layout
      if(n*2*sz <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = sz*2;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = sz*2;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      if(n*4*sz <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = sz*4;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = sz*4;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
    }

    sz=4;
    start1=start;
    if(start%4 != 0) start1 += (4 - (start%4));
    n = (end - start1 + 1)/4;
    if(is_pow_2(n) && (end-start1+1)%4 == 0) {
      if(n*sz <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = sz;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = sz;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      // narrowing
      if(n*2 <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = 2;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = 2;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      if(n*1 <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = 1;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = 1;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      //f2's field layout could be a widening permutation of f1's field layout
      if(n*2*sz <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = sz*2;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = sz*2;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
    }

    sz=8;
    start1=start;
    if(start%8 != 0) start1 += (8 - (start%4));
    n = (end - start1 + 1)/8;
    if(is_pow_2(n) && (end-start1+1)%8 == 0) {
      if(n*sz <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = sz;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = sz;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      // narrowing
      if(n*4 <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = 4;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = 4;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      if(n*2 <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = 2;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = 2;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
      if(n*1 <= bytes_remaining) {
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16);
	m_ads[m_ads_ind].size = 1;
	m_ads[m_ads_ind++].n = n;
	m_ads[m_ads_ind].type = (start1<<32) + (end << 16)+1;
	m_ads[m_ads_ind].size = 1;
	m_ads[m_ads_ind++].n = n;
      }
      assert(m_ads_ind <= PER_ARG_LIM);
    }
  }
 
  shuffle_adaptors_fieldsub(m_ads, m_ads_ind);

  if(calculating) {
    num_adaptors_g *= m_ads_ind;
    printf("memsub: m_ads_ind = %d\n", m_ads_ind);
  }

  for(i=0; i<m_ads_ind; i++) {
    m[fieldnum].type = m_ads[i].type;
    m[fieldnum].size= m_ads[i].size;
    m[fieldnum].n= m_ads[i].n;
    end = (m_ads[i].type>>16) & (0xffff);
    generate_struct_adaptors_randomized(end+1, fieldnum+1);
  }
}
