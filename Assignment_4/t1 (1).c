#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t1.h"

#define GRAPHSIZE 1024

int print = 1;

typedef struct queue
{
  int items[GRAPHSIZE];
  int front;
  int end;
} queue;

queue *createQueue()
{
  struct queue *q = malloc(sizeof(struct queue));
  q->front = -1;
  q->end = -1;
  return q;
}

struct node *CreateNode(int vertex)
{
  struct node *newNode = (struct node *)malloc(sizeof(struct node));
  newNode->vertex = vertex;
  newNode->next = NULL;
  return newNode;
}
Graph *create_graph(int num_nodes)
{
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->numNodes = num_nodes;
  graph->list = malloc(num_nodes * sizeof(struct node *));
  graph->visited = malloc(num_nodes * sizeof(int));

  int i=0;
  for ( i = 0; i < num_nodes; ++i)
  {
    graph->list[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}

void add_edge(Graph *g, int from, int to)
{
  struct node *newNode = CreateNode(to);
  newNode->next = g->list[from];
  g->list[from] = newNode;
  
}

void reset_graph(Graph *g, int origin)
{
  struct node *temp = g->list[origin];

  g->visited[origin] = 0;

  while (temp != NULL)
  {
    int i = temp->vertex;

    if (g->visited[i] == 1)
    {
      reset_graph(g, i);
    }
    temp = temp->next;
  }
}

void dfs(Graph *g, int origin)
{
  
  if(print == 1)
  {
    printf("DFS:");
    print = 0;
  }
  struct node *temp = g->list[origin];

  g->visited[origin] = 1;
  printf(" %c ", ('A' + origin));

  while (temp != NULL)
  {
    int i = temp->vertex;

    if (!g->visited[i])
    {
      dfs(g, i);
    }
    temp = temp->next;
  }
}

void bfs(Graph *g, int origin)
{
  reset_graph(g, origin);
  struct queue *q = createQueue();
  printf("\nBFS ");

  g->visited[origin] = 1;
  if (q->end == GRAPHSIZE - 1)
    printf("\nQueue is Full!!");
  else
  {
    if (q->front == -1)
      q->front = 0;
    q->end++;
    q->items[q->end] = origin;
  }

  while (q->end != -1)
  {
    int currentVertex;
	  if (q->end == -1)
	  {
	    printf("Queue is empty");
	    currentVertex = -1;
	  }
	  else
	  {
	    currentVertex = q->items[q->front];
	    q->front++;
	    if (q->front > q->end)
	    {
	      q->front = q->end = -1;
	    }
	  }
    
    
    printf(" %c ", ('A' + currentVertex));

    struct node *temp = g->list[currentVertex];

    while (temp)
    {
      int adjVertex = temp->vertex;

      if (g->visited[adjVertex] == 0)
      {
        g->visited[adjVertex] = 1;
        if (q->end == GRAPHSIZE - 1)
	    printf("\nQueue is Full!!");
	  else
	  {
	    if (q->front == -1)
	      q->front = 0;
	    q->end++;
	    q->items[q->end] = adjVertex;
	  }
      }
      temp = temp->next;
    }
  }
  free(q);
}



void delete_graph(Graph *g)
{
  free(g->visited);
  free(g);
}

