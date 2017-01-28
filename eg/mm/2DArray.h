
int **Allocate2DArray( int nRows, int nCols)
{
  int i;
  //(step 1) allocate memory for array of elements of column
  //int **ppi = new int*[nRows];
  int **ppi = (int **) malloc(sizeof(int *) * nRows);
  
  //(step 2) allocate memory for array of elements of each row
  //int *curPtr = new int [nRows * nCols];
  int *curPtr = (int *) malloc(sizeof(int) * nRows * nCols);

  // Now point the pointers in the right place
  for( i = 0; i < nRows; ++i)
    {
      *(ppi + i) = curPtr;
      curPtr += nCols;
    }
  return ppi;
}

void Free2DArray(int** Array)
{
  int i;
  free(*Array);
  free(Array);
}
