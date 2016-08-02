#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct _s1 {
  int a;
  int b;
} struct1;

typedef struct _s2 {
  int a;
  int b;
} struct2;

//Assuming this adaptor maps s1's fields to s2
typedef struct _adaptor {
  int field1;
  int field2;
} adaptor_struct;
//Global adaptor object for f1 <- f2
adaptor_struct the_adaptor;

int f1(struct1 *s) {
  if(s) {
    // s->a = 1;
    //return s->a - s->b;
    return s->b;
  }
  return 0;
}

int f2(struct2 *s) {
  if(s) {
    // s->b = 1;
    // return s->b - s->a;
    return s->a;
  }
  return 0;
}

int adapted_f1(struct1 *s1p) {
  int ret;
  //1. Make an object of struct2
  struct2 *s2p = (struct2 *) malloc(sizeof(struct2));
  
  if(!s1p) return 0;
  
  //2. Adapt target object to inner object as per adaptor
  //adapt_s1_to_s2(s1p, s2p, ap);
  if(the_adaptor.field1 == 0) s2p->a = s1p->a;
  else if(the_adaptor.field1 == 1) s2p->a = s1p->b;
  else {
    s2p->a=0; //Something bad happened
    printf("the_adaptor field1 setup incorrectly\n");
  }

  if(the_adaptor.field2 == 0) s2p->b = s1p->a;
  else if(the_adaptor.field2 == 1) s2p->b = s1p->b;
  else {
    s2p->b=0; //Something bad happened
    printf("the_adaptor field2 setup incorrectly\n");
  }
  
  //3. Call adapted inner function
  ret = f2(s2p);

  //4. Apply inverse of adaptor to map inner object to target object
  //adapt_s2_to_s1(s2p, s1p, ap);
  if(the_adaptor.field1 == 0) s1p->a = s2p->a;
  else if(the_adaptor.field1 == 1) s1p->b = s2p->a;
  else { 
    s1p->a=0; //Something bad happened
    printf("the_adaptor field1 setup incorrectly\n");
  }

  if(the_adaptor.field2 == 0) s1p->a = s2p->b;
  else if(the_adaptor.field2 == 1) s1p->b = s2p->b;
  else {
    s1p->b=0; //Something bad happened
    printf("the_adaptor field2 setup incorrectly\n");
  }

  //5. Return saved return value
  return ret;
}

int compare(long *r1p, long *r2p,
	    long a0, long a1, long a2, long a3, long a4, long a5) {
  
  printf("Starting f1\n");  
  fflush(stdout);

  long r1 = f1(a0);
  
  printf("Completed f1\n");
  fflush(stdout);
  
  printf("Starting adapted_f1\n");
  fflush(stdout);
  
  long r2 = adapted_f1(a0);
  
  printf("Completed adapted_f1\n");
  fflush(stdout);
  
  if (r1 == r2) {
    printf("Match\n");
  } else {
    printf("Mismatch\n");
  }
  if (r1p)
    *r1p = r1;
  if (r2p)
    *r2p = r2;
  return r1 == r2;
}

//    int main() {
//      struct1 s1_obj;
//      
//      //This is concrete adaptor
//      ap.field1=2;
//      ap.field2=1;
//      
//      s1_obj.a = 0;
//      s1_obj.b = 255;
//      
//      printf("%d %d\n", f1(&s1_obj), adapted_f1(&s1_obj));
//    }

long global_arg0, global_arg1, global_arg2,
    global_arg3, global_arg4, global_arg5;
void fuzz_start() {}

int main(int argc, char **argv) { 
  FILE *fh;
  if (argc == 5 && argv[3][0]=='f') {
    fh = fopen(argv[4], "r");
  }
  fuzz_start();

    if (argc < 4) {
	fprintf(stderr, "Usage: two-funcs <f1num> <f2num> a [0-6 args]\n");
	fprintf(stderr, "    or two-funcs <f1num> <f2num> g\n");
	fprintf(stderr, "    or two-funcs <f1num> <f2num> f <fname or ->\n");
	exit(1);
    }
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
	  int is_eq = compare(0, 0, a, b, c, d, e, f);
	    if (!is_eq)
		exit(1);
	}
	printf("All tests succeeded!\n");
    } else {
	fprintf(stderr, "Unhandled command argument\n");
	exit(1);
    }
    return 0;
}
