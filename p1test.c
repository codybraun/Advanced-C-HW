#include <stdio.h>
#include <stdlib.h>

 
typedef struct searcher_ {
  double * index;
  int ** pointers;
  int length;
} searcher;

searcher * search2 (float ** arrays, int n, int ** count){
  int i,j,x,minIndex = 0;
  int y = 0;
  float previousMin, min = 2147483647.00;
  searcher * returnSearcher;
  float * returnArray = malloc(sizeof(float)*n);
  int * indexCounter ;
  int total=0;
 
  indexCounter = malloc (sizeof(int) * n);
  
  for (i=0; i<n; i++)
    {
      indexCounter[i] = 0;    
      total += *count[i];
    }
 
  returnSearcher = malloc (sizeof(searcher));
  returnSearcher -> index = malloc(total*sizeof(float));
  returnSearcher -> pointers = malloc(total*sizeof(int*));
  returnSearcher -> pointers[0]= malloc(sizeof(int*)*n);

  for (x=0; x < total; x++){

    min = 100000000;
    for (i=0; i< n; i++){

      if (arrays[i][indexCounter[i]]<=min)
	{
	  min = arrays[i][indexCounter[i]];
	}
    }
     
    if (min != previousMin && x !=0)
      {
	y ++;
	returnSearcher -> pointers[y]= malloc(sizeof(int*)*n);
      }
    
    previousMin = min;
    returnSearcher -> index[y] = min;
    
    for (i=0; i< n; i++){
     
      if (arrays[i][indexCounter[i]] == min)
	{
	  returnSearcher -> pointers[y][i] = indexCounter[i];
	  indexCounter[i]++;
	}
      else
	{	   	   
	 
	  returnSearcher -> pointers[y][i]=indexCounter[i];
	  
	}
    } 
  }
  returnSearcher->length = y;
  printf ("test: pointers[3][3] is %d", returnSearcher->pointers[3][3]);
  return returnSearcher; 
}

int * searcher2Find (searcher * searchStruct, float x)

{
  int end;
  int size = 0;
  int begin, middle;  
  end = searchStruct->length;
  middle = (begin+end)/2;
  while (begin <= end){
     
    if (searchStruct->index[middle] > x)
      {
	end = middle -1;
      }
    else if (searchStruct->index[middle] < x)
      {
	begin = middle + 1;
      }
    else
      { 
	return searchStruct->pointers[middle];
	break;
      } 
    middle = (begin+end)/2;
  }
} 

float * search1 (float ** arrays, int n, double x, int ** count){
  int k = 0;
  int i = 0;
  int end = 0;
  int size = 0;
  int begin, middle; 
  float * returnArray;
  returnArray = malloc(sizeof(float)*n);
  
  for (i = 0; i < n; i ++){
    size = *count[i];
  
    end = size-1;
    begin = 0;
    middle = (begin+end)/2;
    
    while (begin <= end){
     
      if (arrays[i][middle] > x)
	{
	  end = middle -1;
	}
      else if (arrays[i][middle] < x)
	{
	  begin = middle + 1;
	}
      else
	{  
	 
	  returnArray[i] = arrays[i][middle];
	  break;
	} 
      middle = (begin+end)/2;
    }
  } 
  return returnArray; 
}

int main (int argc, char ** argv){
  FILE * file;
  int ** count;
  int i =0;
  int j = 0;
  int k =0;
  float ** arrays;
  float * value;
  searcher * searcher2;
  int * results; 
  /*parse this beast*/

  count = malloc(1000 * sizeof(int *)); /*fix this*/
  file = fopen("arrays.txt", "r");

  arrays = malloc(sizeof(float*)*1000);
  value = malloc (sizeof(float)*100000); 
  count[0] = malloc(1111111111);
  while (fscanf (file, "%d", count[k])!=0)
    {
    
      if (feof(file)){
	break;
      }
      
      printf ("count is %d", *count[k]);
      arrays[i] = malloc(111111111111);
      i++;
      for (j=0; j<*count[k]; j++)
	{ 
	  fscanf (file, "%f", value);
	 
	  arrays[k][j] = *value;
	}
      k++;
        count[k] = malloc(111111111);
    }
  
  search1 (arrays, i , 3.00, count);
  
  searcher2 = search2 (arrays, i, count); /*set up the sercher struct*/
  results = searcher2Find (searcher2, 3.000); 
  
  return 0;
}
  

  
  

    

