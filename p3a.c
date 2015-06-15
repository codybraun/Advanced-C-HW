#include <stdio.h>
#include <stdlib.h>

typedef struct Tree_node{
  struct Tree_node *left, *right;
  int data;
} Tree_node;

int treeCheck (Tree_node * tree){
 
  if (tree->left==NULL && tree->right==NULL)
    {
    return 1;
    }

  int rightMargin = (1<<31);
  int leftMargin = 0;

}

int main (int argc, char ** argv)
{
  return 0;
}
