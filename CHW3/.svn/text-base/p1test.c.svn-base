#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include<time.h>

/* used this thing about limits so I could have sentinel values http://www.tutorialspoint.com/c_standard_library/limits_h.htm */

typedef struct searcher_ {
  double * index;
  int ** pointers;
  int length;
} searcher;



searcher ** search3 (double ** arrays, int length, int ** count)
{
  int i = 0 ;
  int j = 0;
  int u =0;
  int x = 0;
  int y = 0;
  int z = 0;
  searcher ** returnSearcher;
  printf ("length is %d", length);
  returnSearcher = malloc (sizeof(searcher) * length);
  
  for (i=0; i<length-1; i++){
    returnSearcher[i]= malloc(sizeof(searcher)); 
    u = *(count[i]) + *(count[i+1]);
   
    returnSearcher[i]->pointers = malloc(sizeof(int *) * u);
    returnSearcher[i]->pointers[0] = malloc(sizeof(int) * u);
    returnSearcher[i]->pointers[1] = malloc(sizeof(int) * u);
    returnSearcher[i]->index = malloc(sizeof(double) * u);
    returnSearcher[i]->length = 0;
    j=0;
    x=0;
    y=0;
    while (j<u-1)
      {
	if (arrays[i][x] < arrays[i+1][y])
	  {
	    
	    returnSearcher[i]->index[j]=arrays[i][x];
	    returnSearcher[i]->pointers[0][j] = x;
	    returnSearcher[i]->pointers[1][j] = y;
	    returnSearcher[i]->length++;
	    x ++;
	    j++;
	  }
	
	else if (arrays[i][x] > arrays[i+1][y])
	  {
	    
	    returnSearcher[i]->index[j]=arrays[i+1][y];
	    returnSearcher[i]->pointers[0][j] = x;
	    returnSearcher[i]->pointers[1][j] = y;
	    returnSearcher[i]->length++;
	    y ++;
	    j ++;
	    
	  }
	
	else if (arrays[i][x] == arrays[i+1][y])
	  {
	    
	    u--;  
	    returnSearcher[i]->index[j]=arrays[i][x];
	    returnSearcher[i]->pointers[0][j] = x;
	    returnSearcher[i]->pointers[1][j] = y;
	    returnSearcher[i]->length++;
	    y ++;
	    x++;
	    j++;
	  }
      }    
  }
  
  
  for (i=0; i<*count[length]; i++){
    returnSearcher[length]->pointers[0][i]=i;
    returnSearcher[length]->pointers[0][i]=INT_MAX;
  }
 
  return returnSearcher;
}

searcher * search2 (double ** arrays, int n, int ** count){
  int i,j,x,minIndex = 0;
  int y = 0;
  double previousMin, min = 2147483647.00;
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
  returnSearcher -> index = malloc(total*sizeof(double));
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
  return returnSearcher; 
}

int * searcher2Find (searcher * searchStruct, double x)

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

int * search3Find (searcher ** searchStruct, double x, int n)
{
  int * returnArray;
  int i = 0;
  int j = 0;
  int z = 0;
  int y= 0;
  int end;
  int size = 0;
   int begin =0;
   int middle;
  returnArray = malloc (sizeof(int) * n);
  end = searchStruct[0]->length;
  middle = (begin+end)/2;

   
  while (begin <= end){
    
    if (searchStruct[0]->index[middle] > x)
      {
	end = middle -1;
      }
    else if (searchStruct[0]->index[middle] < x)
      {
	begin = middle + 1;
      }
    else
      { 

	i= searchStruct[0]->pointers[0][middle];
	break;
      } 
    middle = (begin+end)/2;
  }
 
  i= searchStruct[0]->pointers[0][middle];
  
  for (j=0; j < n-2; j++)
    {
      returnArray[z]= i;
      y =  searchStruct[z]->pointers[1][i]; 
      z ++;
      i =  searchStruct[z]->pointers[0][y];
    }
  return returnArray;
}  

double * search1 (double ** arrays, int n, double x, int ** count){
  int k = 0;
  int i = 0;
  int end = 0;
  int size = 0;
  int begin, middle; 
  double * returnArray;
  returnArray = malloc(sizeof(double)*n);
  
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
  double ** arrays;
  double * value, x;
  searcher * searcher2, ** searcher3;
  int * results, * results2;
  double random;
  clock_t start, end, test1, test2, test3;
  /*parse this beast*/
  x=0;
  count = malloc(1000 * sizeof(int *)); /*fix this*/
  file = fopen("arrays.txt", "r");
  
  arrays = malloc(sizeof(double*)*1000);
  value = malloc (sizeof(double)*100000); 
  count[0] = malloc(1111111111);
  
  while (fscanf (file, "%d", count[k])!=0)
    {  
      if (feof(file)){
	 break;
       }
       arrays[k] = malloc(sizeof(double*) * (*count[k]));    
 
       for (j=0; j<*count[k]; j++)
	 { 
	  
	   fscanf (file, "%lf", value);
	   x = *value;
	   arrays[k][j] = x;
	 }
       k++;
       count[k] = malloc(sizeof(int));
    }

 
  /*
  search1 (arrays, k , 3.00, count);
  searcher2 = search2 (arrays, k, count);
  results = searcher2Find (searcher2, 3.000); 
  searcher3 = search3(arrays, k, count);
  results2 = search3Find (searcher3, 1.00005, k);
  */


  start = clock();
  for (j=0; j<100000; j++)

    {
      random = rand()/10000;
       search1 (arrays, k , random, count);
    }
  end = clock();
  test1 = (end - start)/CLOCKS_PER_SEC;
  printf ("test 1 was %d", (int) test1);
  
  searcher2 = search2 (arrays, k, count);
  start = clock();
  for (j=0; j<100000; j++)

    {
      random = rand()/10000;
      searcher2Find (searcher2, random); 
    }
  end = clock();
  test2 = (end - start)/CLOCKS_PER_SEC;
  printf ("test 2 was %d", (int) test2);
  
  searcher3 = search3(arrays, k, count);
 
  start = clock();
  for (j=0; j<100000; j++)
    {
      random = rand()/10000;
      search3Find (searcher3, random, k); 
    }
  end = clock();
  test3 = (end - start)/CLOCKS_PER_SEC;
  printf ("test 3 was %d", (int) test1);
 
  return 0;
}
  


  
  

    

