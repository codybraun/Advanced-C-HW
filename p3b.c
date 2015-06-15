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

int BSTcheck (Tree_node * tree){
  
  if (rangeCheck (tree, -2147483647, 2147483647))
    {
      printf ("Valid tree");
      return 1;
    } 
  else
    {
      printf ("Invalid tree");
      return -1;
    }
}

int main (int argc, char ** argv){
  Tree_node *a,*b,*c,*d,*e;
  a = nTree (5);
  b = nTree (2);
  b->right = nTree(3);
  b->right->right = nTree(4);
  BSTcheck (b);
  return 0;
}
