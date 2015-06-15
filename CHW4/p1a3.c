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
    i=0;
    int * dists, k, min, y;
    int * done;
    j=0;
    z=0;
    n = x->vCount;

    distArray = (int**) malloc (n * sizeof(int*));
    
	startT = clock();
	
    for (i=0; i < n; i++) {
		done = (int *) malloc (sizeof(int)*n);
    dists = (int *) malloc (n * sizeof(int));
        for (z=0; z< x->vCount; z++)
        {
            dists[z]= MAXINT;
            done[z]= 0;
        }
		
		/*Dijkstras*/
		
        dists[i] = 0;
        z = i;
        while (done[z] == 0)
        {
            for (j=0; j< n; j++)
            {
                if (x->adj[z][j]==1)
                {
                    if (dists[z] + x->weights[z][j] < dists[j])
                    {
                        dists[j]= dists[z] + x->weights[z][j];
                    }
                }
            }
            done[z]=1;
            min = MAXINT;
            for (k=0; k < x->vCount; k++)
            {
                if (dists[k] < min && done[k]==0)
                {
                    min = dists[k];
                    y = k;
                }
            }
            z = y;
        }
                distArray[i]=dists;
                            free(done);
        free(dists);

    }
    

        endT = clock();
    printf ("All shortest paths time: %f \n", (float) endT-startT / (CLOCKS_PER_SEC));
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






























