#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define OMP_NUM_THREADS 16
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
    int * dists, i, j, k, min, y, lc, gc, lcv, gcv, n, firstV, lastV, doneCount;
    int * done;
    n = x->vCount;
    done = (int * )malloc (sizeof(int)*n);
    dists = (int *) malloc (sizeof(int)*n);

    for (i=0; i<n; i++) /*initialize support arrays*/
    {
        dists[i]= MAXINT;
        done[i]= 0;
    }
    dists[s] = 0;
    i = s;


    gcv = MAXINT;

    #pragma omp parallel private(j, lc, lcv, k, firstV, lastV) shared (i, dists, done, gc, gcv, x, n, doneCount)
    {
        firstV = (omp_get_thread_num() * n) / OMP_NUM_THREADS;	/*assign each thread a chunk of the adj matrix*/
        lastV = (((omp_get_thread_num() + 1) * n) / OMP_NUM_THREADS) -1;
        lcv = MAXINT;

        while (doneCount != n)
        {
            for(j=firstV; j<=lastV ; j++)
            {
                /*printf ("adj[%d][%d] is %d", i, j,x->adj[i][j]);*/
                if (x->adj[i][j]==1)
                {
                    if (dists[i] + x->weights[i][j] < dists[j])
                    {
                        dists[j]= dists[i] + x->weights[i][j];

                        if (done[j] ==0 && dists[j] <= lcv) {	/*if j isn't completed and is lower than than current lowest value, update*/
                            lcv = dists[j];
                            lc = j;

                        }
                    }
                }

                if (gcv > lcv) {
                    #pragma omp critical /*update the global closest value*/
                    {
                        gcv = lcv;
                        gc = lc;
                        lcv = MAXINT;	/*reset local closest vertex*/
                    }
                }


            }
            #pragma omp barrier	/*not positive I need this here, but erring on the safe side*/
            #pragma omp single
            {

                done[i] = 1;
                doneCount++;
                i = gc;
            }
        }
    }
    free(done);
    return dists;
}

int ** sps (graph * x)
{
    int ** distArray;
    distArray = malloc (x->vCount * sizeof(int*));
    int i;
    clock_t startT,endT;
    startT = clock();
    for (i=0; i<x->vCount; i++)
    {
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
    printf ("n at read is %d", n);
    x->vCount = n;
    weights = (int **) malloc(n*sizeof(int*));
    adjList = (int **) malloc(n*sizeof(int*));
    for(i=0; i<n; i++) {
        weights[i] = (int *) malloc (n*sizeof(int));
        adjList[i] = (int *) malloc (n*sizeof(int));
    }

    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            weights[i][j]=0;
            adjList[i][j]=0;
        }
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

    char input[50];
    char * fInput[50];
    FILE * graphFile;
    clock_t startT,endT;
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

        else if (strcmp (fInput[0], "single")==0) {
            if (fInput[1]==NULL)
            {
                fInput[1]="";
            }
            x = read (fInput[1], 0);
            startT = clock();
            dijkstra(0, x);

            endT = clock();
            printf ("Single-source time: %f \n", (double) endT-startT / (CLOCKS_PER_SEC));

        }



    }
    return 0;


}































