//taken from https://software.intel.com/en-us/courseware/256200
#include <assert.h>
#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>

#include "2DArray.h"
#define THRESHOLD  32768 /* product size below which matmultleaf is used */  

//void seqMatMult(int m, int n, int p, int** A, int** B, int** C)   
long f1(int** A, int** B, int** C)   
//long f1(int** A, int** B, int** C, int sz)   
{
  int i, j, k, sz=N;
  assert(sz==N);
  for ( i = 0; i < sz; i++)   
    for ( j = 0; j < sz; j++)    
      {          
	C[i][j] = 0;   
	for ( k = 0; k < sz; k++)   
	  C[i][j] += A[i][k]*B[k][j];   
      }  
  return 0;
}  

long f2(int **C, int **A, int **B)
//long f2(int **C, int **A, int **B, int sz)
{   
  int m, n, p, sz=N;
  assert(sz==N);
  m=n=p=sz;
  strassenMMult(m, n, p, A, B, C);
  return 0;
}
 
void matmultleaf(int ml, int nl, int pl, int **A, int **B, int **C)    
/*  
    subroutine that uses the simple triple loop to multiply  
    a submatrix from A with a submatrix from B and store the  
    result in a submatrix of C.   
*/  
// mf, ml; /* first and last+1 i index */  
// nf, nl; /* first and last+1 j index */  
// pf, pl; /* first and last+1 k index */  
{    
  int i,j,k;
  for ( i = 0; i < ml; i++)   
    for ( j = 0; j < nl; j++) {
      int temp=0;  
      for ( k = 0; k < pl; k++)   
	temp += A[i][k]*B[k][j]; 
      C[i][j]=temp;
    } 
} 


void copyQtrMatrix(int **X, int m, int **Y, int mf, int nf)
{
  int i;
  for ( i = 0; i < m; i++) 
    X[i] = &Y[mf+i][nf];
}

void AddMatBlocks(int **T, int m, int n, int **X, int **Y)
{
  int i,j;
  for ( i = 0; i < m; i++)
    for ( j = 0; j < n; j++)
      T[i][j] = X[i][j] + Y[i][j];
}

void SubMatBlocks(int **T, int m, int n, int **X, int **Y)
{
  int i,j;
  for ( i = 0; i < m; i++)
    for ( j = 0; j < n; j++)
      T[i][j] = X[i][j] - Y[i][j];
}

long mul_2(int **a, int **b, int **c) {
    int i,j;
    int m1,m2,m3,m4,m5,m6,m7;

    m1= (a[0][0] + a[1][1])*(b[0][0]+b[1][1]);
    m2= (a[1][0]+a[1][1])*b[0][0];
    m3= a[0][0]*(b[0][1]-b[1][1]);
    m4= a[1][1]*(b[1][0]-b[0][0]);
    m5= (a[0][0]+a[0][1])*b[1][1];
    m6= (a[1][0]-a[0][0])*(b[0][0]+b[0][1]);
    m7= (a[0][1]-a[1][1])*(b[1][0]+b[1][1]);

    c[0][0]=m1+m4-m5+m7;
    c[0][1]=m3+m5;
    c[1][0]=m2+m4;
    c[1][1]=m1-m2+m3+m6;

    return 0;
}

void strassenMMult(int ml, int nl, int pl, int **A, int **B, int **C)
{
  int i,j,k;
  //if (ml*nl*pl < THRESHOLD) 
  //if(ml==2 && nl ==2 && pl==2)
  //mul_2(A, B, C);
  //matmultleaf(ml, nl, pl, A, B, C);
  if(ml*nl*pl > N*N*N) exit(1);
  if(ml==1 && nl==1 && pl==1) 
    C[0][0]=A[0][0]*B[0][0];
  else {
    int m2 = ml/2;
    int n2 = nl/2;
    int p2 = pl/2;

    int **M1 = Allocate2DArray(m2, n2);
    int **M2 = Allocate2DArray(m2, n2);
    int **M3 = Allocate2DArray(m2, n2);
    int **M4 = Allocate2DArray(m2, n2);
    int **M5 = Allocate2DArray(m2, n2);
    int **M6 = Allocate2DArray(m2, n2);
    int **M7 = Allocate2DArray(m2, n2);

    int **wAM1 = Allocate2DArray(m2, p2);
    int **wBM1 = Allocate2DArray(p2, n2);
    int **wAM2 = Allocate2DArray(m2, p2);
    int **wBM3 = Allocate2DArray(p2, n2);
    int **wBM4 = Allocate2DArray(p2, n2);
    int **wAM5 = Allocate2DArray(m2, p2);
    int **wAM6 = Allocate2DArray(m2, p2);
    int **wBM6 = Allocate2DArray(p2, n2);
    int **wAM7 = Allocate2DArray(m2, p2);
    int **wBM7 = Allocate2DArray(p2, n2);

    //int **A11 = new int*[m2];
    int **A11 = (int **) malloc(sizeof(int *) * m2);
    //int **A11 = pool_ppi; pool_ppi+=m2;
    //int **A12 = new int*[m2];
    int **A12 = (int **) malloc(sizeof(int *) * m2);
    //int **A12 = pool_ppi; pool_ppi+=m2;
    //int **A21 = new int*[m2];
    int **A21 = (int **) malloc(sizeof(int *) * m2);
    //int **A21 = pool_ppi; pool_ppi+=m2;
    //int **A22 = new int*[m2];
    int **A22 = (int **) malloc(sizeof(int *) * m2);
    //int **A22 = pool_ppi; pool_ppi+=m2;

    //int **B11 = new int*[p2];
    int **B11 = (int **) malloc(sizeof(int *) * p2);
    //int **B11 = pool_ppi; pool_ppi += p2;
    //int **B12 = new int*[p2];
    int **B12 = (int **) malloc(sizeof(int *) * p2);
    //int **B12 = pool_ppi; pool_ppi += p2;
    //int **B21 = new int*[p2];
    int **B21 = (int **) malloc(sizeof(int *) * p2);
    //int **B21 = pool_ppi; pool_ppi += p2;
    //int **B22 = new int*[p2];
    int **B22 = (int **) malloc(sizeof(int *) * p2);
    //int **B22 = pool_ppi; pool_ppi += p2;

    //int **C11 = new int*[m2];
    int **C11 = (int **) malloc(sizeof(int *) * m2);
    //int **C11 = pool_ppi; pool_ppi += m2;
    //int **C12 = new int*[m2];
    int **C12 = (int **) malloc(sizeof(int *) * m2);
    //int **C12 = pool_ppi; pool_ppi += m2;
    //int **C21 = new int*[m2];
    int **C21 = (int **) malloc(sizeof(int *) * m2);
    //int **C21 = pool_ppi; pool_ppi += m2;
    //int **C22 = new int*[m2];
    int **C22 = (int **) malloc(sizeof(int *) * m2);
    //int **C22 = pool_ppi; pool_ppi += m2;

    copyQtrMatrix(A11, m2, A,  0,  0);
    copyQtrMatrix(A12, m2, A,  0, p2);
    copyQtrMatrix(A21, m2, A, m2,  0);
    copyQtrMatrix(A22, m2, A, m2, p2);

    copyQtrMatrix(B11, p2, B,  0,  0);
    copyQtrMatrix(B12, p2, B,  0, n2);
    copyQtrMatrix(B21, p2, B, p2,  0);
    copyQtrMatrix(B22, p2, B, p2, n2);

    copyQtrMatrix(C11, m2, C,  0,  0);
    copyQtrMatrix(C12, m2, C,  0, n2);
    copyQtrMatrix(C21, m2, C, m2,  0);
    copyQtrMatrix(C22, m2, C, m2, n2);

    {
      // M1 = (A11 + A22)*(B11 + B22)
      AddMatBlocks(wAM1, m2, p2, A11, A22);
      AddMatBlocks(wBM1, p2, n2, B11, B22);
      strassenMMult(m2, n2, p2, wAM1, wBM1, M1);
    }

    {
      //M2 = (A21 + A22)*B11
      AddMatBlocks(wAM2, m2, p2, A21, A22);
      strassenMMult(m2, n2, p2, wAM2, B11, M2);
    }

    {
      //M3 = A11*(B12 - B22)
      SubMatBlocks(wBM3, p2, n2, B12, B22);
      strassenMMult(m2, n2, p2, A11, wBM3, M3);
    }

    {
      //M4 = A22*(B21 - B11)
      SubMatBlocks(wBM4, p2, n2, B21, B11);
      strassenMMult(m2, n2, p2, A22, wBM4, M4);
    }

    {
      //M5 = (A11 + A12)*B22
      AddMatBlocks(wAM5, m2, p2, A11, A12);
      strassenMMult(m2, n2, p2, wAM5, B22, M5);
    }

    {
      //M6 = (A21 - A11)*(B11 + B12)
      SubMatBlocks(wAM6, m2, p2, A21, A11);
      AddMatBlocks(wBM6, p2, n2, B11, B12);
      strassenMMult(m2, n2, p2, wAM6, wBM6, M6);
    }

    {
      //M7 = (A12 - A22)*(B21 + B22)
      SubMatBlocks(wAM7, m2, p2, A12, A22);
      AddMatBlocks(wBM7, p2, n2, B21, B22);
      strassenMMult(m2, n2, p2, wAM7, wBM7, M7);
    }

    for ( i = 0; i < m2; i++)
      for ( j = 0; j < n2; j++) {
	C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
	C12[i][j] = M3[i][j] + M5[i][j];
	C21[i][j] = M2[i][j] + M4[i][j];
	C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
      }

    Free2DArray(M1);
    Free2DArray(M2);
    Free2DArray(M3);
    Free2DArray(M4);
    Free2DArray(M5);
    Free2DArray(M6);
    Free2DArray(M7);

    Free2DArray(wAM1);
    Free2DArray(wBM1);
    Free2DArray(wAM2);
    Free2DArray(wBM3);
    Free2DArray(wBM4);
    Free2DArray(wAM5);
    Free2DArray(wAM6);
    Free2DArray(wBM6);
    Free2DArray(wAM7);
    Free2DArray(wBM7);

    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(C11); free(C12); free(C21); free(C22);
  }
}


int CheckResults(int m, int n, int **C, int **C1)
{
#define ERR_THRESHOLD 1
  //
  //  May need to take into consideration the floating point roundoff error
  //    due to parallel execution
  //
  int i, j, k;
  for ( i = 0; i < m; i++) {
    for ( j = 0; j < n; j++) {
      if (abs(C[i][j] - C1[i][j]) > ERR_THRESHOLD ) {
        printf("%d  %d\n", C[i][j], C1[i][j]);
        return 1;
      }
    }
  }
  return 0;
}
 
int old_main(int argc, char* argv[])   
{
  //initialize();
  //printf("initial pool_ppi=0x%x pool_ptr = 0x%x\n", pool_ppi, pool_ptr);
  clock_t before, after;

  //if (argc != 2) {
  //  printf("Usage: %s <N> \n", argv[0]);
  //  exit(1);
  //}
  //int N = atoi(argv[1]);
  //if(N%2 != 0) N++;

  int **A = Allocate2DArray(N, N);
  int **B = Allocate2DArray(N, N);
  int **C = Allocate2DArray(N, N);
  int **C4 = Allocate2DArray(N, N);

  int i, j;   

  for (i = 0; i < N; i++) {   
    for (j = 0; j < N; j++) {   
      //A[i][j] = 5 - ((int)(rand()%100) / 10); 
      A[i][j]=i+j+1;
    }      
  }   

  for (i = 0; i < N; i++) {   
    for (j = 0; j < N; j++) {   
      //B[i][j] = 5 - ((int)(rand()%100) / 10);  
      B[i][j] = i+j+6;
    }      
  }   

  printf("Execute Standard matmult  N = %d  N = %d  N = %d\n\n", N, N, N);
  before = clock();
  f1(A, B, C);
  after = clock();
  printf("Standard matrix function done in %7.2f secs\n\n\n",(float)(after - before)/ CLOCKS_PER_SEC);

  before = clock();
  f2(C4, A, B);
  after = clock();
  printf("Strassen matrix function done in %7.2f secs\n\n\n",(float)(after - before)/ CLOCKS_PER_SEC);

  if (CheckResults(N, N, C, C4)) 
    printf("Error in matmultS\n\n");
  else
    printf("OKAY\n\n");

  Free2DArray(A);
  Free2DArray(B);
  Free2DArray(C);
  Free2DArray(C4);

  return 0;   
}  
