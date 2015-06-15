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

int ** sps (graph * x)
{
    clock_t startT,endT;
    int ** distArray;
    int i, j, n, z;
    int ** dists, k, min, y;
    int ** done;
    j=0;
    n = x->vCount;  
     dists = (int **) malloc(n*sizeof(int*));
    done = (int **) malloc(n*sizeof(int*));

    for(i=0; i<n; i++) {
        dists[i] = (int *) malloc (n*sizeof(int));
        done[i] = (int *) malloc (n*sizeof(int));
    }
        startT = clock();

    for (i=0; i < n; i++) { /*this loop is all sources*/
    z =0;
        for (z=0; z< n; z++)
        {
            dists[i][z]= MAXINT;
            done[i][z]= 0;
        }

        /*Dijkstras*/
        dists[i][i] = 0;
        z = i;
        while (done[i][z]==0)	/*keep going until can't get to another vertex to add to S*/
        {
            for (j=0; j< n; j++)
            {
                if (x->adj[z][j]==1)
                {
				
                    if (dists[i][z] + x->weights[z][j] < dists[i][j])	/*Relax*/
                    {

                        dists[i][j]= dists[i][z] + x->weights[z][j];
                    }
                }
            }
            done[i][z]=1;
            min = MAXINT;
            for (k=0; k < n; k++)
            {
                if (dists[i][k] < min && done[i][k]==0) /*look for next clsoest vettex*/
                {
                    min = dists[i][k];
                    y = k;
                }
            }
            z = y;
                    
        }
    }
    endT = clock();

    printf ("All shortest paths time: %f \n", (float) endT-startT / (CLOCKS_PER_SEC));

    return dists;
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
