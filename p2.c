#include <stdlib.h>
#include <stdio.h>

typedef struct Tree_node{
  struct Tree_node *left, *right;
  int data;
} Tree_node;

int BSTcheck (Tree_node * tree){

 tree * temp = tree;
 int * list, * first;
 int i=0;

 if (temp->left==NULL && temp->right==NULL){
   return 1;
 }

 while (temp->left != NULL && temp->right !=NULL){ 
   
   if (temp-> left == NULL)
     {
       list[i] = temp-> data;
       i ++;
       temp = temp -> right;
     }
   else 
     {
       first = temp->left;
       
       while (first->right != NULL) /*find largest element left of temp*/
	 {
	   first = first->right;
	 }
	   
       if (first->right == NULL)
	 {
	   first->right = temp;
	   temp = temp->left;
	 }
       
       
     }
 }
 
}

int main (int argc, char ** argv){


  return 0;
}
