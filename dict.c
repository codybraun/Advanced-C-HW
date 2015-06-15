#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*I used Brass as a source for a fair bit of this*/

typedef struct tree_ {
  struct tree_ * left;
  struct tree_ * right;
  char * key;  
}
  tree;


tree * nTree() {
  tree * tempT = (tree *) malloc(sizeof(tree));
  tempT-> left = NULL;
  tempT-> right = NULL;
  tempT-> key = malloc(500);
  return tempT;
}

void delete (tree * dict, char * word)
{
  tree * sTree, * tTree;
  tree * temp = dict;
  tTree = nTree();
  sTree = nTree();
  
  if ((dict->left == NULL) && (dict-> right == NULL))
    {     
      printf ("1The word %s was not found in the dictionary \n", word);
    }
  
  if (dict-> right == NULL)
    {  
      if (strcmp ((char *) dict->key, (char *) word)==0)
	{
	  dict->left = NULL;
	}
      else
	{
	  printf ("2The word %s was not found in the dictionary \n", word);
	  return;
	}
    }
  
  while (temp->right != NULL) /*not at leaf*/
    {
      tTree = temp;
      if (strcmp((char *) word,(char *)temp->key) < 0){
	 temp = tTree -> left;
	 sTree = tTree -> right; 
       }
       else
	 {
	   temp = tTree -> right;
	   sTree = tTree -> left;
	 }
    }
  
  if (strcmp((char *) word,(char *) temp->key)!=0){
    printf ("3The word %s was not found in the dictionary", word);
    return;
  }
  else 
    {
      tTree -> key = sTree -> key;
      tTree -> right = sTree -> right;
      tTree -> left = sTree -> left;
    }
  printf ("Succesfully removed %s", word);
}

void findWord (tree * dict, char * word)
{
  if (dict->left==NULL){
    printf ("1%s was not found in the dictionary \n", word); 
  }
  
  if ((dict->right == NULL)){
    printf ("print comparing %s and %s", (char *) dict->key, word);
    if (strcmp ((char *) dict->key, (char *) word)==0)
      {
	printf ("%s : %s \n", dict->key, (char *) dict->left);
      }
    else
	{
	  printf ("2%s was not found in the dictionary \n", word); 
	}
  }

  else
    {
      printf ("print comparing %s and %s", (char *) dict->key, word);
      if (strcmp((char *) word, (char *) dict->key)<0){
	printf ("looking left");
	findWord (dict->left, word);
      }
      else 
	{
	  printf ("looking right");
	  findWord (dict->right, word);
	}
    }  
} 

void treePrint (tree * dictionary)
{
  if (dictionary->right == NULL && dictionary->left == NULL){
    printf ("This dictionary is empty \n");
  }
  else  if (dictionary->right == NULL){
    printf ("%s : %s \n", (char *) dictionary->key, (char *) dictionary->left);
      }
  else 
    {
      treePrint (dictionary->left);
      treePrint (dictionary->right);
    }    
}

void insertWord (tree * dict, char * word, char * definition)
{
  char * def = malloc(1000);
  tree * oleaf, * nleaf, * temp;
  strcpy (def, definition);
 
  if (dict->left == NULL) /*empty tree, just throw it on*/
    {
      dict->right = NULL;
      dict->left = (tree *) def;
      strcpy(dict->key, word);
    }
  else
    {
      temp = dict;
      while (temp->right != NULL)
	{ 
	  if (strcmp ((char *) word, (char *) temp->key) <0){
	    temp = temp->left; 
	  }
	  else
	    {
	      temp = temp->right;
	    }
	}
      
      if (strcmp((char *) temp->key, (char *) word)==0)
	{
	  printf ("%s is already in the dictionary", word);
	  return;
	}
      
      oleaf = nTree();
      oleaf->left = temp->left;
      strcpy (oleaf->key, temp->key);
      oleaf-> right = NULL;
      
      nleaf = nTree();
      nleaf->left = (tree *) def;
      strcpy(nleaf->key,(char *) word);
      nleaf->right = NULL;

      if (strcmp(((char *) temp->key),(char *) word)<0)
	{
	  temp -> left = oleaf;
	  temp -> right = nleaf;
	  strcpy (temp -> key, word);
	}
      else
	{
	  temp-> left = nleaf;
	  temp-> right = oleaf;
	}
    } 
  
}

int main (int argc, char** argv){
  tree * dictionary;
  dictionary = nTree();
  int exit,i = 0;
  char input[100];
  char * fInput[50];
  
  while (exit != 1)
    {
    printf ("Enter a command: ");
    fgets(input, 500, stdin);
    fInput[0] = strtok(input, " ");
    fInput[1] = strtok(NULL, " "); 
    fInput[2] = strtok(NULL, "'"); 
    
    if (strcmp (fInput[0], "add")==0) {  
      printf ("Added %s with definition: %s",fInput[1], fInput[2]);
      insertWord (dictionary, fInput[1], fInput[2]);
      
    }
    

    else if (strcmp (fInput[0], "find")==0) {  
      findWord (dictionary, fInput[1]);
      
    }


    else if (strcmp (fInput[0], "delete")==0) {  
      delete (dictionary, fInput[1]);
      
    }
     
    else if (strcmp (fInput[0], "print")==0) 
    {  
 
      treePrint (dictionary);
    }

    else
      {
	printf ("command not found, please try print, insert WORD, delete WORD, or find WORD");
      }
  
    }
  return 0;
}
