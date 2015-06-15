#include<stdlib.h>
#include<string.h>
#include <time.h>
#include<stdio.h>
#include "chtbl.h"
#define LFMIN .2
#define LFMAX .75

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


typedef struct word_ {
    char * key;
    char * def;
}
word;

word * newWord(char * wordKey, char * wordDef) {
    word * tempW = (word *) malloc(sizeof(word));
    tempW-> def = malloc(500*sizeof(char));
    tempW-> key = malloc(50*sizeof(char));
    strcpy (tempW->def, wordDef);
    strcpy (tempW->key, wordKey);
    return tempW;
}

int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data)) {
    int i;

    if ((htbl->table = (List *) malloc(buckets*sizeof(List))) == NULL)
        return -1;

    htbl->buckets = buckets;

    for (i = 0; i < htbl->buckets; i++)
        list_init(&htbl->table[i], NULL, NULL, NULL);

    htbl->h = h;
    htbl->destroy = destroy;
    htbl->match = match;
    htbl->size = 0;
    return 0;
}

/* insert an object into the hashtable */
int chtbl_insert(CHTbl *htbl, const void *data) {
    int error_code;
    int bucket;
    if (chtbl_lookup(htbl,(void **) &data) == 0) /*data already in table */
        return 1;
    /* data not in table, find bucket to place it in */
    /* note that f, in particular the division method, is hardwired
       into the line below as the mod operation
    */
    bucket = (htbl->h(data)) % (htbl->buckets);
    if ((error_code = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
        htbl->size++;
    return error_code;
}

int chtbl_lookup(const CHTbl *htbl, void **data) {
    ListElmt *element;
    int bucket;
    bucket = (htbl->h(*data)) % (htbl->buckets); /* apply user's g and hardwired f */
    for (element = list_head(&htbl->table[bucket]); element != NULL; element =
                list_next(element)) {
        if (htbl->match(*data, list_data(element))) {
            *data = list_data(element); /* set pointer to point to object found in table */
            return 0;
        }
    }

    return -1;
}

void print (const CHTbl * htbl)
{
    int i =0;
    int j =0;
    word ** sortedDict;
    word * temp;
    ListElmt *element;
    sortedDict = malloc(550*htbl->size);
    temp = malloc(sizeof(word));
    /*insertion sort is slow, but quick to code and this wasn't going to be real efficient either way*/
    for (i=0; i<htbl->buckets; i++) {
        for (element = list_head(&htbl->table[i]); element != NULL; element =
                    list_next(element)) {
            sortedDict[j]= (word *) list_data(element);
            j++;
        }
    }

    for (j = 1; j < htbl->size; j++)
    {
        i=j;
        while (i>0 && (strcmp (sortedDict[i]->key, sortedDict[i-1]->key)<0))
        {
            temp = sortedDict[i];
            sortedDict[i] = sortedDict[i-1];
            sortedDict[i-1] = temp;
            i--;
        }

    }

    for (j =0; j < htbl->size; j++)
    {
        printf ("%s : %s \n", ((word *) sortedDict[j])->key, ((word *) sortedDict[j])->def);
    }
}

int lookupRange (word * find, word * find2, CHTbl * hDict)
{
    int  i=0;
    ListElmt *element;
    for (i=0; i<hDict->buckets; i++) {
        for (element = list_head(&hDict->table[i]); element != NULL; element =
                    list_next(element)) {
            if((strcmp(((word *) list_data(element))->key, find->key) >=0) && (strcmp(((word *) list_data(element))->key, find2->key) <= 0))
            {
                printf ("%s : %s \n", ((word *) list_data(element))->key, ((word *) list_data(element))->def);
            }
        }
    }
    return 0;
}

int h1 (const void * input) { /*obviously, this is a pretty bad function, just wanted it for comparison */
    int len, i, k;
    char * string;
    i=0;
    k=0;

    string = ((word *) input)->key;

    len = strlen(string);

    for (i=0; i< len; i++)
    {
        k+= (int) string[i];
    }


    return k;
}

int h2 (const void * input) {
    int len, i, k;
    char * string;

    string = ((word *) input)->key;
    len = strlen(string);

    for (i=0; i< len; i++)
    {
        k^= string[i];
    }

    return k;
}

int h3 (const void * input) { /* got the general rotating hash idea here: http://burtleburtle.net/bob/hash/examhash.html*/
    int len, i, k;
    char * string;

    string = ((word *) input)->key;
    len = strlen(string);

    for (i=0; i< len; i++)
    {
        k = (k<<2) ^ (k>>8) ^ (int) string[i];
    }


    return k;
}

int h (const void * input) { /*http://en.wikipedia.org/wiki/Jenkins_hash_function*/
    int len, i, k;
    char * string;

    string = ((word *) input)->key;
    len = strlen(string);

    for (i=0; i< len; i++)
    {
        k += string[i];
        k += (k << 8);
        k ^= (k >> 6);
    }


    return k;
}



int match (const void * input, const void * input2) {
    if (!(strcmp( ((word *)input)->key, ((word *) input2)->key)))
        return 1;
    else
        return 0;
}

void destroy (void * input) {

}

void freeTable(CHTbl * hDict)
{
    int i;
    ListElmt * element;
    for (i=0; i<hDict->buckets; i++)
    {
        for (element = list_head(&hDict->table[i]); element != NULL; element =
                    list_next(element)) {
            free (element);

        }
    }
    free(hDict->table);

}


void rehash (CHTbl * hDict)
{
    /*wikipedia is actually pretty helpful about rehashing http://en.wikipedia.org/wiki/Hash_table#Dynamic_resizing*/
    ListElmt *element;
    int i=0;
    int doRehash=0;
    FILE * log;
    int newBuckets;
    CHTbl hDict2;
    newBuckets = 0;


    if ((double)hDict->size/(double)hDict->buckets > LFMAX) {
        newBuckets = hDict->buckets*2;
        doRehash=1;
    }
    else if ((double)hDict->size/(double)hDict->buckets < LFMIN)
    {
        newBuckets = hDict->buckets/2;
        doRehash=1;
    }

    if (doRehash) {
        chtbl_init(&hDict2, newBuckets, &h, &match, &destroy);
        for (i=0; i < hDict->buckets; i++)
        {
            for (element = list_head(&hDict->table[i]); element != NULL; element = list_next(element))
            {
                chtbl_insert(&hDict2, (void *) list_data(element));
            }
        }
        log = fopen("p1log.txt", "r+");
        fseek(log, 0 , SEEK_END);
        fprintf (log, "REHASING \n");
        fclose(log);

        freeTable(hDict);
        * hDict = hDict2;

    }

}

int read (CHTbl * hDict, char * fileName, FILE * log)
{
    char * item, * item2, * item3;
    word * add;
    FILE * fileToOpen = fopen(fileName, "r");
    item = malloc(550);
    item2 = malloc(500);
    item3 = malloc(500);

    while (fgets(item, 550, fileToOpen) >0)
    {
        item2 = strtok(item, " ");
        item3 = strtok(NULL, "\"");
        add = newWord (item2, item3);
        chtbl_insert(hDict, (void *) add);
        log = fopen("p1log.txt", "r+");
        fseek(log, 0 , SEEK_END);
        fprintf (log, "load factor is now %.3f \n", (double)hDict->size/(double)hDict->buckets);
        fclose(log);
        rehash(hDict);
    }

    fclose(fileToOpen);
    return 0;
}

int delete (CHTbl *hDict, void *delete) {
    int bucket;
    ListElmt *element;
    void * data;
    bucket = hDict->h(delete) % hDict->buckets;
    printf ("looking in bucket %i", bucket);
    for (element = list_head(&hDict->table[bucket]); element != NULL; element =
                list_next(element)) {

        if (hDict->match(data, list_data(element))) {
            data = list_data(element); /* set pointer to point to object found in table */
            list_rem_next(&hDict->table[bucket], NULL, (const void **) data);
            hDict->size --;
        }
    }



}

int main (int argc, char ** argv)

{
    int exit1 = 0;
    int i;
    int n;
    clock_t startT,endT;
    char input[100];
    char * printC, * string;
    char * fInput[500];
    float lf;
    word * add, * find, *deleteW, *find2, *findTest;
    CHTbl hDict;
    FILE * log = fopen("p1log.txt", "w");
    chtbl_init(&hDict, 4, &h, &match, &destroy);


    while (exit1 != 1)
    {

        printf ("\nEnter a command: ");
        fgets(input, 500, stdin);
        printC = strtok(input,"\n");

        if (strcmp (printC, "print")==0)
        {
            print (&hDict);
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

                add = newWord (fInput[1], fInput[2]);
                chtbl_insert(&hDict, (void *) add);
                log = fopen("p1log.txt", "r+");
                fseek(log, 0 , SEEK_END);
                lf = ((double)hDict.size/(double)hDict.buckets);
                fprintf (log, "load factor is now %.3f \n", lf);
                fclose(log);
                rehash(&hDict);
            }

            else if (strcmp (fInput[0], "find")==0) {
                if (fInput[2]== NULL) {
                    find = newWord (fInput[1], fInput[1]);
                    if (chtbl_lookup(&hDict, (void **) &find)==0) {
                        printf ("%s : %s", find->key, find->def);
                    }
                    else
                    {
                        printf ("not found");
                    }

                }
                else
                {
                    find = newWord (fInput[1], fInput[1]);
                    find2 = newWord (fInput[2], fInput[2]);
                    lookupRange(find, find2, &hDict);
                }

            }

            else if (strcmp (fInput[0], "delete")==0) {
                deleteW = newWord (fInput[1], fInput[1]);
                delete (&hDict, deleteW);
                rehash(&hDict);
            }

            else if (strcmp (fInput[0], "read")==0) {
                read (&hDict, fInput[1], log);
                printf ("File %s read.", fInput[1]);
            }
            else if (strcmp (fInput[0], "test")==0) {
                startT = clock();
                n = atoi(fInput[1]);
                for (i=0; i<n; i++)
                {
                    string = randS(6);
                    findTest = newWord(string, string);
                    chtbl_insert(&hDict, (void *) findTest);


                }
                endT = clock();
                printf ("Insert time: %f \n", (double) endT-startT / (CLOCKS_PER_SEC));
                startT = clock();
                for (i=0; i<n; i++)
                {

                    string = randS (6);
                    findTest = newWord(string, string);
                    chtbl_lookup(&hDict, (void **) &findTest);
                    log = fopen("p1log.txt", "r+");
                    fseek(log, 0 , SEEK_END);
                             lf = ((double)hDict.size/(double)hDict.buckets);
                    fprintf (log, "load factor is now %.3f \n", lf);
                    fclose(log);
                    rehash(&hDict);

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









