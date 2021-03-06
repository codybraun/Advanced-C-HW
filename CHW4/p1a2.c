#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXINT 10000000

typedef struct graph_ {
    int vCount;
    int  ** weights;
    int ** adj;
} graph;

graph * nGraph() {
    graph * tGraph = malloc(sizeof(graph));
    tGraph->vCount = 0;
    tGraph -> weights = NULL;
    tGraph -> adj = NULL;
    return tGraph;
}

int * dijkstra (int s, graph * x)
{
    int * dists, i, j, k, min, y;
    int * done;
    done = malloc (sizeof(int)*x->vCount);
    i =0;
    dists = malloc (x->vCount * sizeof(int));

    for (i=0; i<x->vCount; i++)
    {
        dists[i]= MAXINT;
        done[i]= 0;
    }
    dists[s] = 0;
    i = s;
    while (done[i]==0)
    {
        for (j=0; j< x->vCount; j++)
        {
            if (x->adj[i][j]==1)
            {

                if (dists[i] + x->weights[i][j] < dists[j])
                {
                    dists[j]= dists[i] + x->weights[i][j];
                }
            }

        }
        done[i]=1;
        min = MAXINT;
        for (k=0; k < x->vCount; k++)
        {
            if (dists[k] < min && done[k]==0)
            {
                min = dists[k];
                y = k;
            }


        }
        i = y;
    }
        free(done);
    return dists;
}

int ** sps (graph * x)
{
    int ** distArray;
      clock_t startT,endT;
    distArray = (int **) malloc (x->vCount * sizeof(int*));
    int i, n;
    n = x->vCount;
    i=0;
    startT = clock();

    for (i = 0; i < x->vCount; i++) {
        distArray[i]= dijkstra(i, x);
    }
       endT = clock();
                printf ("All shortest paths time: %f \n", (double) endT-startT / (CLOCKS_PER_SEC));
                
    return distArray;
}

graph * read (char * fileName, int print)
{
	  clock_t startT,endT;
    char * item, * item2, * item3, * item4;
    FILE * graphFile = fopen(fileName, "r");
    graph * x;
    int ** adjList, ** weights, i, n, j;
    item = malloc(100);
    fgets (item, 100, graphFile);
    x = nGraph();

                startT = clock();

    n = atoi(item);
    x->vCount = n;
    weights = (int **) malloc(n*sizeof(int*));
    adjList = (int **) malloc(n*sizeof(int*));
    for(i=0; i<n; i++) {
        weights[i] = (int *) malloc (n*sizeof(int));
        adjList[i] = (int *) malloc (n*sizeof(int));

    }

    while (fgets (item, 100, graphFile) >0)
    {
        item2 = strtok(item, " ");
        item3 = strtok(NULL, " ");
        item4 = strtok(NULL, " ");
        adjList[atoi(item2)][atoi(item3)] = 1;
        weights[atoi(item2)][atoi(item3)] = atoi(item4);
    }
    
        x->adj = adjList;
    x->weights = weights;

    fclose(graphFile);
     endT = clock();
               printf ("Read time: %f \n", (double) endT-startT / (CLOCKS_PER_SEC));
    
    return x;
}

int main (int argc, char** argv) {
  clock_t startT,endT;
    char input[50];
    char * fInput[50];
    FILE * graphFile;
    int exit = 0;
    int ** distArray, i, j;
    graph * x;
    while (exit != 1)
    {
        printf ("\nEnter a command: ");
        fgets(input, 60, stdin);
        fInput[0] = strtok(input, " ");
        fInput[1] = strtok(NULL, "\n");

        if (strcmp (fInput[0], "read")==0) {
            if (fInput[1]==NULL)
            {
                fInput[1]="";
            }
            x = read (fInput[1], 0);
            distArray= sps(x);
        }


        else if (strcmp (fInput[0], "print")==0) {
            if (fInput[1]==NULL)
            {
                fInput[1]="";
            }
            x = read (fInput[1], 0);
            distArray= sps(x);

            for (i=0; i< x->vCount; i++) {
                for (j=0; j< x->vCount; j++) {
                    printf ("distArray[%d][%d] = %d ", i, j , distArray[i][j]);
                }
                printf ("\n");
            }

        }

    }
    return 0;


}



























