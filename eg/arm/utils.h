#define MAX_ADAPTERS 1000000
#define MAX_TESTS 100000
typedef struct { int a,b,c,d,e,f,g,h,i,j,k,l,m; } test; 
test tests[MAX_TESTS];
int fnum;

int f1(int a, int b, int c, int d, int e, int f,
	int g, int h, int i, int j, int k, int l, int m) {
  return (funcs[fnum].fptr)(a, b, c, d, e, f,g,h,i,j,k,l,m);
}
