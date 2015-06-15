#include <stdlib.h>
#include <stdio.h>

typedef struct Tree_node_ {
  struct Tree_node_ *left, *right;
  int data;
} Tree_node;


Tree_node * nTree(int x) {
  Tree_node * tempT;
  tempT = (Tree_node *) malloc(sizeof(Tree_node));
  tempT-> left = NULL;
  tempT-> right = NULL;
  tempT-> data = x;
  return tempT;
}

int BSTcheck (Tree_node * tree){
  Tree_node * temp, * first;
  int * list;
  int j = 0;
  int i = 0; 
  list = malloc (10000);
  temp = tree;
  
  while (temp!=NULL)
    {     
      if (temp-> left != NULL)
	{ 
	  first = temp-> left;
	  while (first->right != NULL && first-> right != temp){
	    first = first -> right;
	    /* get the largest element to the left*/
	  }
	  
	  if (first->right==NULL){
	    first->right = temp;
	    temp = temp-> left;
	    /* this is lower, make make temp the lower right child*/
	  }
	  else
	    {
	      first-> right = NULL;
	      temp = temp-> right;
	    }
	}
      else
	{
	  list[i] = temp->data;
	  i++;
	  temp = temp->right;
	}
      
    }
  
  for (j=0; j< i-1; j++)
    {
      /* this should be in-order, check it*/
      if (list[j] > list[j+1])
	{
	  printf ("Not a valid tree \n");
	  return -1;
	  
	}
    }
  printf ("Valid tree \n");
  return 1;
}

int main (int argc, char ** argv){
  Tree_node *a,*b,*c,*d,*e;
  a = nTree (5);
  b = nTree (2);
  b->right = nTree(3);
  b->right->right = nTree(1);
  BSTcheck (b);
  return 0;
}
