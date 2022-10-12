#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "t2.h"

void init(Graph *g)
{
    int i, j;
    for (i = 0; i < MAX_VERTICES; i++)
        for (j = 0; j < MAX_VERTICES; j++)
            g->matrix[i][j] = 0;
}

Graph *create_graph(int num_nodes)
{
    Graph *g = malloc(sizeof(Graph));
    g->numNodes = num_nodes;
    init(g);

    return g;
}


void add_edge(Graph *g, int from, int to, int weight)
{
    g->matrix[from][to] = weight;
    g->matrix[to][from] = weight;
}

void display(int distance[], int n, int origin)
{
    int i=0;
    for ( i = 0; i < n; i++)
    {
        printf("\nThe length of the shortest path between %c and %c is %d", 'A' + origin, 'A' + i, distance[i]);
    }
}


void dijkstra(Graph *g, int origin)
{
    int distance[MAX_VERTICES];
    int flag[MAX_VERTICES];
	int i=0;
    for (i = 0; i < MAX_VERTICES; i++)
    {
        distance[i] = INT_MAX;
        flag[i] = 0;
    }
    distance[origin] = 0;
	i =0;
    for (i = 0; i < g->numNodes; i++)
    {
    	
    	int min = INT_MAX;
	    int x;
		int i=0;
	    while (i < MAX_VERTICES)
	    {
	        if (!flag[i] && distance[i] < min)
	        {
	            min = distance[i];
	            x = i;
	        }
	        i++;
	    }
        flag[x] = 1;
        printf("%c ", 'A' + x);
        int y=0;
        for (y = 0; y < MAX_VERTICES; y++)
        {
            if ((!flag[y] && g->matrix[x][y] && (distance[x] != INT_MAX)) && (distance[x] + g->matrix[x][y] < distance[y]))
            {
                distance[y] = distance[x] + g->matrix[x][y];
            }
        }
    }
    display(distance, g->numNodes, origin);
}

void delete_graph(Graph *g)
{
    free(g);
}


