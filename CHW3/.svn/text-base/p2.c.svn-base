#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*I used Brass chapter 3 as a reference*/

/* got the idea for this random string generator off the internet http://codereview.stackexchange.com/questions/29198/random-string-generator-in-c hopefully that's okay, just wanted something for tests*/
char *randS(size_t len){
    int j =0;
    int i;
    static char chars[] ="abcdefghijklmnopqrstuvwxyz";
    char *string =NULL;
        string = malloc(sizeof(char)* (len +1));

            for (j = 0; j < len; j++) {
                int i = rand()% (int)(sizeof(chars)-1);
                string[j]= chars[i];
            }
            string[len] = '\0';
        
    
    return string;
}

typedef struct tree_ {
    struct tree_ * left;
    struct tree_ * right;
    struct tree_ * parent;
    char * key;
    enum {RED, BLACK} color;
}
tree;


tree * nTree() {
    tree * tempT = (tree *) malloc(sizeof(tree));
    tempT-> left = NULL;
    tempT-> right = NULL;
    tempT-> parent = NULL;
    tempT-> key = malloc(50);
    tempT -> color = BLACK;
    return tempT;
}

void lRotate (tree * t)
{

    char * word = malloc(500);
    tree * tParent, * temp;
    temp = t->left;
    word = t->key;
    t->left = t-> right;
    t -> key = t-> right->key;
    t -> right = t->left->right;
    t->right->parent =t;
    t->left->right = t->left->left;
    t->left->right->parent=t->left;
    t->left->left = temp;
    t->left->left->parent = t->left;
    t->left->key = word;

}

void rRotate (tree * t)
{

    char * word = malloc(500);
    tree * tParent, * temp;
    temp = t->right;
    word = t->key;
    t->right = t-> left;
    t -> key = t-> left->key;
    t -> left = t->right->left;
    t->left->parent =t;
    t->right->left = t->right->right;
    t->right->left->parent=t->right;
    t->right->right = temp;
    t->right->right->parent = t->right;
    t->right->key = word;
}


/* for debugging*/
void printTree (tree * dictionary)
{
    if (dictionary->right == NULL) {
        printf ("parent key: %s", dictionary->parent->key);
        printf("leaf key: %s ", dictionary->key);
        if (dictionary->color==RED)
        {
            printf (" color: red\n");
        }
        else
        {
            printf (" color: black\n");
        }
    }
    else
    {
        if (dictionary->parent != NULL) {
            printf ("parent key: %s", dictionary->parent->key);
        }
        printf("key : %s", dictionary->key);
        if (dictionary->color==RED)
        {
            printf (" color: red\n");
        }
        else
        {
            printf (" color: black\n");
        }
        if (dictionary->parent==NULL) {
            printf ("parent key is null");
        }
        printf("left child: (");
        printTree(dictionary->left);
        printf (")");
        printf("right child: (");
        printTree(dictionary->right);
        printf (")");
    }
}

int delete (tree * dict, char * word)
{
    tree * sTree, * tTree, * other, *upper;
    tree * temp = dict;
    int exit;
    tTree = nTree();
    sTree = nTree();


    if ((dict->left == NULL) && (dict-> right == NULL))
    {
        printf ("1The word %s was not found in the dictionary \n", word);
    }

    while (temp->right != NULL) /*not at leaf*/
    {
        tTree = temp;
        if (strcmp((char *) word,(char *)temp->key) <= 0) {
            temp = tTree -> left;
            sTree = tTree -> right;
        }
        else
        {
            temp = tTree -> right;
            sTree = tTree -> left;
        }
    }

    if (strcmp((char *) word,(char *) temp->key)!=0) {
        printf ("3The word %s was not found in the dictionary", word);
        return;
    }
    else
    {
        tTree -> key = sTree -> key;
        tTree -> right = NULL;
        tTree -> left = sTree -> left;
    }
    
    /*rebalance*/

    while (tTree->parent != NULL && exit ==0) /*fix or get back up to the root*/
    {
        if (tTree->color == RED) { /*Can always fix RB properties at a red */
            tTree->color = BLACK;
            exit=1;
        }
        else if (tTree->parent->left == tTree) { /*tTree is a left child*/
            other = tTree -> parent -> right;
            upper = tTree -> parent;

            if (upper->color == BLACK && other->color == BLACK && other-> left -> color == BLACK) {
                lRotate (upper);
                upper->left->color = RED;
                upper->color = BLACK;
                tTree = tTree->parent;

            }
            else if (upper->color == BLACK && other->color == BLACK && other-> left -> color == RED) {
                rRotate(other);
                lRotate(upper);
                upper->color= BLACK;
                upper->left->color= BLACK;
                upper->right->color= BLACK;
                exit=1;
            }

            else if (upper->color == BLACK && other->color == RED && other->left->left!= NULL && other-> left ->left-> color == BLACK) {
                lRotate(upper);
                lRotate(upper->left);
                upper->left->left->color= RED;
                upper->left->color= BLACK;
                upper->color = BLACK;
                exit=1;
            }

            else if (upper->color == BLACK && other->color == RED && other->left->left != NULL && other-> left ->left-> color == RED) {
                lRotate(upper);
                printTree (upper->left->right);
                rRotate(upper->left->right);

                lRotate(upper->left);
                upper->left->left->color= BLACK;
                upper->left->right->color= BLACK;
                upper->color = BLACK;
                upper->left->color = RED ;
                exit=1;
            }

            else if (upper->color == RED && other->color == BLACK && other->left-> color == BLACK) {
                lRotate(upper);
                upper->left->left->color= BLACK;
                upper->left->color= RED;
                upper->color = BLACK;
                exit=1;
            }

            else if (upper->color == RED && other->color == BLACK && other-> left-> color == RED) {
                rRotate(other);
                lRotate(upper);
                upper->left->color= BLACK;
                upper->right->color= BLACK;
                upper->color = RED;
                exit=1;
            }

        }
        else
        {   /*tTree is a right child*/

            other = tTree -> parent -> left;
            upper = tTree -> parent;

            if (upper->color == BLACK && other->color == BLACK && other-> right -> color == BLACK) {
                rRotate (upper);
                upper->right->color = RED;
                upper->color = BLACK;
                tTree = tTree->parent;
            }

            else if (upper->color == BLACK && other->color == BLACK && other-> right-> color == RED) {
                lRotate(other);
                rRotate(upper);
                upper->color= BLACK;
                upper->left->color= BLACK;
                upper->right->color= BLACK;
                exit=1;
            }

            else if (upper->color == BLACK && other->color == RED && other->right->right!= NULL && other-> right -> right -> color == BLACK) {
                rRotate(upper);
                rRotate(upper->right);
                upper->right->right->color= RED;
                upper->right->color= BLACK;
                upper->color = BLACK;
                exit=1;
            }

            else if (upper->color == BLACK && other->color == RED && other->right->right!= NULL && other-> right -> right-> color == RED) {
                rRotate(upper);
                lRotate(upper->right->left);
                rRotate(upper->right);
                upper->right->right->color= BLACK;
                upper->right->left->color= BLACK;
                upper->color = BLACK;
                upper->right->color = RED ;
                exit=1;
            }
            else if (upper->color == RED && other->color == BLACK && other->right-> color == BLACK) {
                rRotate(upper);
                upper->right->color= RED;
                upper->color = BLACK;
                exit=1;
            }

            else if (upper->color == RED && other->color == BLACK && other-> right-> color == RED) {
                lRotate(other);
                rRotate(upper);
                upper->left->color= BLACK;
                upper->right->color= BLACK;
                upper->color = RED;
                exit=1;
            }

        }

    }

    tTree->color = BLACK;
    printf ("Succesfully removed %s", word);
    return 0;

}

void findWord (tree * dict, char * word)
{
    if (dict->left==NULL) {
        printf ("%s was not found in the dictionary \n", word);
    }

    if ((dict->right == NULL)) {

        if (strcmp ((char *) dict->key, (char *) word)==0)
        {
            printf ("%s : %s \n", dict->key, (char *) dict->left);
        }
        else
        {
            printf ("%s was not found in the dictionary \n", word);
        }
    }

    else
    {

        if (strcmp((char *) word, (char *) dict->key)<=0) {
            findWord (dict->left, word);
        }
        else
        {

            findWord (dict->right, word);
        }
    }
}

void findWordRange (tree * dict, char * word, char * word2)
{

    if ((dict->right == NULL)) {

        if (strcmp((char *) word, (char *) dict->key)<=0 && strcmp((char *) word2, (char *) dict->key)>=0)
        {
            printf ("%s : %s \n", dict->key, (char *) dict->left);
        }

    }

    else
    {

        if (strcmp((char *) word, (char *) dict->key)<=0 && strcmp((char *) word2, (char *) dict->key)>=0) {

            findWordRange (dict->left, word, word2);
            findWordRange (dict->right, word, word2);
        }
        else if (strcmp((char *) word, (char *) dict->key)>0 && strcmp((char *) word2, (char *) dict->key)>=0)
        {

            findWordRange (dict->right, word, word2);
        }
        else if (strcmp((char *) word, (char *) dict->key)<=0 && strcmp((char *) word2, (char *) dict->key)<0)
        {
            findWordRange (dict->right, word, word2);
        }

    }
}

void treePrint (tree * dictionary)
{
    if (dictionary->right == NULL && dictionary->left == NULL) {
        printf ("This dictionary is empty \n");
    }
    else  if (dictionary->right == NULL) {
        printf ("%s : %s \n", (char *) dictionary->key, (char *) dictionary->left);
    }
    else
    {
        treePrint (dictionary->left);
        treePrint (dictionary->right);
    }
}


void insertWord (tree * dict, char * word, char * definition, FILE * log)
{
    int finished = 0;
    char * def = malloc(500);
    tree * oleaf, * nleaf, * temp, * uncle, * temp2;
    uncle = nTree();
    strcpy (def, definition);
    temp = dict;
    if (dict->left == NULL) /*empty tree, just throw it on*/
    {
        dict->right = NULL;
        dict->left = (tree *) def;
        strcpy(dict->key, word);
    }
    else
    {
        while (temp->right != NULL)
        {

            if (strcmp ((char *) word, (char *) temp->key) <=0) {
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
        oleaf -> color = RED;

        nleaf = nTree();
        nleaf->left = (tree *) def;
        strcpy(nleaf->key,(char *) word);
        nleaf->right = NULL;
        nleaf -> color = RED;

        oleaf->parent = temp;
        nleaf->parent = temp;

        if (strcmp(((char *) temp->key),(char *) word)<0)
        {
            temp -> left = oleaf;
            temp -> right = nleaf;

        }
        else
        {
            temp-> left = nleaf;
            temp-> right = oleaf;
            strcpy (temp -> key, word);
        }
    }


    /*that's all pretty much the same, now need to enforce R/B rules */

    if (temp->parent==NULL) {
        temp->color = BLACK;
    }
    else
    {
        while (temp->parent != NULL && temp->color==RED && finished==0)
        {
            if (temp == temp->parent->right)
            {   /* check if the uncle is left child or right child*/

                uncle = temp->parent->left;
            }
            else
            {
                uncle = temp->parent->right;

            }

            if (uncle->color==RED)
            {
                uncle->parent->color = RED;
                temp->color = BLACK;
                uncle->color = BLACK;


            }

            else
            {

                if (temp==temp->parent->left)
                    /*temp is a left child*/
                {

                    if (temp->right->color==BLACK)
                    {
                        rRotate (temp->parent);
                        temp->parent->right->color = RED;

                        finished = 1;
                    }
                    else
                    {
                        lRotate (temp);
                        rRotate (temp->parent);
                        temp->parent->left->color = BLACK;
                        temp->parent->right->color = BLACK;
                        temp->parent->color = RED;

                    }
                }
                else
                {

                    /*temp is right child*/
                    if (temp->left->color==BLACK)
                    {
                        lRotate (temp->parent);
                        temp->parent->left->color = RED;
                        temp->parent->color = BLACK;
                        finished = 1;

                    }
                    else
                    {
                        rRotate (temp);
                        lRotate (temp->parent);
                        temp->parent->left->color = BLACK;
                        temp->parent->right->color = BLACK;
                        temp->parent->color = RED;
                    }
                }

            }

            if (!finished && temp->parent!=NULL && temp->parent->parent != NULL)
            {
                temp = temp->parent->parent;
            }
        }


    }

    fseek(log, 0 , SEEK_END);
    fprintf (log, "height is now %i \n", treeHeight(dict));
    dict->color=BLACK;
}

int treeHeight (tree * dict) {
    int height, lHeight, rHeight;
    if (dict->left == NULL)
    {
        return 0;
    }
    else if (dict->right == NULL) {
        return 1;
    }
    else

    {
        lHeight = 1+ treeHeight(dict->left);
        rHeight = 1+ treeHeight(dict->right);
        if (lHeight > rHeight)
        {
            return lHeight;

        }
        else
        {
            return rHeight;
        }
    }
}

int read (tree * dictionary, char * fileName, FILE * log)
{
    char * item, * item2, * item3;

    FILE * fileToOpen = fopen(fileName, "r");
    item = malloc(550);

    while (fgets (item, 550, fileToOpen) >0)
    {
        item2 = strtok(item, " ");
        item3 = strtok(NULL, "'");
        insertWord (dictionary, item2, item3, log);
    }
    fclose(fileToOpen);
}


int blackNodes(tree *dict)
{
    int left, right;

    if (dict->right == NULL)
    {
        if (dict->color==BLACK)
        {
            return 3;
        }
        else
        {
            return 2;
        }
    }


    left = blackNodes(dict->left);
    right= blackNodes(dict->right);
    if (left == 0 || right ==0 || left != right)
    {
        return 0;
    }
    else

    {

        if (dict->color==BLACK)
        {
            return 1 + right;
        }
        else
        {
            return right;
        }



    }
}

int rbCheck (tree * dict)
{
    if (dict->parent != NULL) {

        if (dict->parent->color==RED && dict->color==RED)
        {
            return 0;
        }
    }

    if (dict->right == NULL)
        return 1;
    else
        return (blackNodes(dict->left)==blackNodes(dict->right) && rbCheck(dict->left) && rbCheck(dict->right));
}

int main (int argc, char** argv) {
    clock_t startT,endT;
    tree * dictionary;
    int exit = 0;
    int n;
    char * string;
    int i;
    char input[500];
    char * printC;
    char * fInput[500];
    dictionary = nTree();
    FILE * log = fopen("p2log.txt", "w");
    while (exit != 1)
    {
        printf ("\nEnter a command: ");
        fgets(input, 550, stdin);
        printC = strtok(input,"\n");

        if (strcmp (printC, "print")==0)
        {
            treePrint (dictionary);
        }
        if (strcmp (printC, "printTree")==0)
        {
            printTree (dictionary);
        }

        else
        {
            fInput[0] = strtok(input, " ");
            fInput[1] = strtok(NULL, " ");
            fInput[2] = strtok(NULL, "'");

            if (strcmp (fInput[0], "insert")==0) {
                if (fInput[2]==NULL)
                {
                    fInput[2]="";
                }/*prevent seg faults from blank definitions*/
                printf ("Added %s with definition: %s \n",fInput[1], fInput[2]);
                log = fopen("p2log.txt", "r+");
                insertWord (dictionary, fInput[1], fInput[2], log);
                fclose(log);
            }

            else if (strcmp (fInput[0], "find")==0) {
                if (fInput[2]== NULL)
                {
                    findWord (dictionary, fInput[1]);
                }
                else
                {

                    findWordRange (dictionary, fInput[1], fInput[2]);
                }

            }


            else if (strcmp (fInput[0], "delete")==0) {
                delete (dictionary, fInput[1]);

            }

            else if (strcmp (fInput[0], "read")==0) {
                read (dictionary, fInput[1], log);

            }

            else if (strcmp (fInput[0], "check")==0) {
                printf ("Check is: %i", rbCheck (dictionary));

            }

            else if (strcmp (fInput[0], "test")==0) {
                startT = clock();
                n = atoi(fInput[1]);
                for (i=0; i<n; i++)
                {
                    string = randS (6);
                    insertWord (dictionary, string, string, log);


                }
                endT = clock();
                printf ("Insert time: %f \n", (double) endT-startT / (CLOCKS_PER_SEC));
                startT = clock();
                for (i=0; i<n; i++)
                {

                    string = randS (6);

                    findWord(dictionary, string);



                }

                endT = clock();
                printf ("Find time: %f \n", (double) endT-startT / (CLOCKS_PER_SEC));
            }


            else
            {
                printf ("command not found, please try print, insert WORD, delete WORD, or find WORD \n");
            }

        }
    }

    return 0;
}
























