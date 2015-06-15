#include <stdio.h>
#include <stdlib.h>

double * search (double ** arrays, int n, double x){
  int i,j,k = 0;
  double * returnArray;
  returnArray = malloc(sizeof(double)*n);
  for (i = 0; i < n; i ++){
    j = (sizeof(arrays[i]))/2;
    k = j/2;
    printf ("j is %d k is %d",j, k);
    while (!(x < arrays[i][j+1] && x > arrays[i][j-1])){
      if (x < arrays[i][j])
	{
	  j = j - k;
	  k = k/2;
	}
      else if (x > arrays[i][j])
	{
	  j = j + k;
	  k = k/2;
	}
    }
      printf ("adding %f ", arrays[i][j]);
      returnArray[i] = arrays[i][j];
  
  }
  
  return returnArray; 
}




int main (int argc, char ** argv)
{
  double testArray[]={1.222,3.444,5.60,7.66,8.99};
  double testArray2[]={1.222,3.444,5.60,7.66,8.99};
  double testArray3[]={1.222,3.444,5.60,7.66,8.99};
  double** tA;
  tA = malloc(sizeof(double*) * 30);
  tA[0] = testArray;
  tA[1] = testArray2;
  tA[2] = testArray3;
  
  search (tA,3, 3.000);
  
  return 0;
}
