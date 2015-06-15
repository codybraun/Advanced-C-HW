#include <stdlib.h>
#include <stdio.h>

/*I looked at wikipedia page about morris traversals for this*/ 

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

int BSTcheckA (Tree_node * tree){
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
	  printf ("Invalid tree detected without recursion \n");
	  return -1;
	  
	}
    }
  printf ("Valid tree detected without recursion \n");
  return 1;
}


int rangeCheck (Tree_node * tree, int low, int high)
{
  if (tree==NULL)
    {
      return 1;
    }
  else if (tree->data < low || tree->data >= high)
    {
      return 0;
    }
  else
    {
      return (rangeCheck (tree->left, low, tree->data) && rangeCheck (tree->right, tree->data, high));  
    }
}

int BSTcheckB (Tree_node * tree){
  
  if (rangeCheck (tree, -2147483647, 2147483647))
    {
      printf ("Valid tree detected recursively\n");
      return 1;
    } 
  else
    {
      printf ("Invalid tree detected recursively\n");
      return -1;
    }
}

int main (int argc, char ** argv){
  Tree_node *a, *b;
  a = nTree (12);
  b = nTree (12);

  a->right = nTree(3);
  a->right->right = nTree(1);
 
  BSTcheckA (a);
  BSTcheckB (a);
  b->right = nTree(13);
  b->left = nTree(5);
  b->left->left = nTree(2);
  b->left->left->left = nTree(0);
  BSTcheckA (b);
  BSTcheckB (b);

  return 0;
}
