#include <stdio.h>
#include <stdlib.h>
 
typedef struct searcher_ {
  double * index;
  int ** pointers;
} searcher;

searcher * search (double ** arrays, int n, int k){
  int i,j,x,y,minIndex = 0;
  double previousMin, min = 2147483647.00;
  searcher * returnSearcher;
  double * returnArray = malloc(sizeof(double)*n);
  int * indexCounter ;
  indexCounter = malloc (sizeof(int) * n);
  for (i=0; i<n; i++)
    {
      indexCounter[i] = 0;
      
    }
 
  returnSearcher = malloc (sizeof(searcher));
  returnSearcher -> index = malloc(k*n*sizeof(double));
  returnSearcher -> pointers = malloc(k*n*sizeof(int*));
  for (x=0; x <n*k; x++){
    min = 1000000;

    for (i=0; i< k; i++){
      if (arrays[i][indexCounter[i]]<=min)
	{
	  min = arrays[i][indexCounter[i]];
	}
    }
 
    
    if (min != previousMin && x !=0)
      {
	y ++;
      }
    
    previousMin = min;
    returnSearcher -> pointers[y]= malloc(100);
    returnSearcher -> index[y] = min;

    for (i=0; i< k; i++){
      if (arrays[i][indexCounter[i]] == min)
	{
	  returnSearcher -> pointers[y][i]=indexCounter[i];

	    indexCounter[i]++;
	 }
       else
	 {	   	   
	   returnSearcher -> pointers[y]= malloc(100);
	    returnSearcher -> pointers[y][i]=indexCounter[i];

	 }
    } 
  } 

return returnSearcher; 
}

int main (int argc, char ** argv)
{
  int i,j = 0;
  double testArray[]={1.222,3.444,5.60,7.66,8.99};
  double testArray2[]={1.222,3.444,5.60,7.66,8.99};
  double testArray3[]={3.444,5.60,7.66,8.99};
  double** tA;
  searcher * lookUp;
  tA = malloc(sizeof(double*) * 30);
  tA[0] = testArray;
  tA[1] = testArray2;
  tA[2] = testArray3;
  
  lookUp = search (tA,4,3);
 
  for (i=0; i<5; i++)
    {
      printf ("The index of lookUp at %d is %f", i, lookUp->index[i]);
      for (j=0; j<3; j++)
	{
	  printf ("pointer [%d][%d] is %d", i, j, lookUp->pointers[i][j]);
	} 
  	} 
  return 0;
}
  
