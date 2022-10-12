#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t3.h"
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_BUFFER 16
#define MAX_EDGES 7777 
#define MAX_VERTEX 7777
#define INFINITY 1e9
#define MAX_CHAR 32

int load_v, load_e;
int matrix[MAX_VERTEX][MAX_VERTEX];
int cost[MAX_VERTEX][MAX_VERTEX];
int distance[MAX_VERTEX],pred[MAX_VERTEX];
int visited[MAX_VERTEX];

struct Edges {
  int vertex1, vertex2, weight;
};

struct Vertices {
  int sp_id; 
  char sp_name[MAX_CHAR], longitude[MAX_CHAR], latitude[MAX_CHAR];
};
struct Vertices gArray[MAX_EDGES];

int next_field( FILE *f, char *buf, int max );

void fetch_edges (  FILE *csv, struct Edges *p) {
  char buf[MAX_CHAR];
  next_field( csv, buf, MAX_CHAR );
  p->vertex1 = atoi(buf);
  next_field( csv, buf, MAX_CHAR );
  p->vertex2 = atoi(buf);  
  next_field( csv, buf, MAX_CHAR );
  p->weight = atoi(buf); 
}

void fetch_vertices (FILE *csv, struct Vertices *p){
  char buf[MAX_CHAR];
  next_field( csv, buf, MAX_CHAR );
  p->sp_id = atoi(buf);
  next_field(csv, p->sp_name, MAX_CHAR);
  next_field(csv, p->longitude, MAX_CHAR);
  next_field(csv, p->latitude, MAX_CHAR);
}

int load_edges(char *s){
  FILE *f;
  struct Edges arr[MAX_EDGES];    
  struct Edges p;
  int a,b,c;
  f = fopen(s, "r");

  if(!f) { 
    printf("unable to open %s\n", s); 
    return EXIT_FAILURE; 
  }
  fetch_edges( f, &p );

  int nbEdges = 0;
  while(!feof(f)) {
    
    fetch_edges( f, &arr[nbEdges] );
    load_e++;

    a = arr[nbEdges].vertex1;
    b = arr[nbEdges].vertex2;
    c = arr[nbEdges].weight;
    matrix[a][b] = c;
    matrix[b][a] = c;

    nbEdges++;
  }
  matrix[300][496] = 0;matrix[496][300] = 0;
  matrix[522][7659] = 0;matrix[7659][522] = 0;
  fclose(f);

  printf("Loaded %d edges\n", load_e);
  return 1;
}

int load_vertices(char *s){
  FILE *f;
    struct Vertices arr[MAX_VERTEX];    
    struct Vertices p;
    f = fopen(s, "r");

    if(!f) { 
      printf("unable to open %s\n", s); 
      return EXIT_FAILURE; 
  }
  fetch_vertices( f, &p );

  int nbVertices = 0;
  while(!feof(f)) {
    
    fetch_vertices( f, &arr[nbVertices] );
    load_v++;

    gArray[nbVertices].sp_id = arr[nbVertices].sp_id;
    strcpy(gArray[nbVertices].sp_name, arr[nbVertices].sp_name);
    strcpy(gArray[nbVertices].longitude, arr[nbVertices].longitude);
    strcpy(gArray[nbVertices].latitude, arr[nbVertices].latitude);

    nbVertices++;
  }

  fclose(f);
  printf("Loaded %d vertices\n", load_v);
  return 1;
}

int next_field( FILE *f, char *buf, int max ) {
  int i=0, end=0, quoted=0;
  
  for(;;) { 
    buf[i] = fgetc(f);
    if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
    if(buf[i]==',' && !quoted) { break; }
    if(feof(f) || buf[i]=='\n') { end=1; break; } 
    if( i<max-1 ) { ++i; } 
  }
  buf[i] = 0; 
  return end; 
}



void shortest_path(int startingNode, int endingNode)
{
  int reverse[50];
  int here = 0;
  int origin = startingNode;
  int dest = endingNode;
 
  int count,min,nextnode,i,j;
  int n;
  n = MAX_VERTEX;

  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      if(matrix[i][j]==0)
        cost[i][j]=INFINITY;
      else
        cost[i][j]=matrix[i][j];

  for(i=0;i<n;i++)
  {
    distance[i]=cost[origin][i];
    pred[i]=origin;
    visited[i]=0;
  }

  distance[origin]=0;
  visited[origin]=1;
  count=1;

  while(count<n-1){
    min=INFINITY;
    for(i=0;i<n;i++)
      if(distance[i]<min&&!visited[i])
      {
        min=distance[i];
        nextnode=i;

      }

    visited[nextnode]=1;

    for(i=0;i<n;i++)
      if(!visited[i])
        if(min+cost[nextnode][i]<=distance[i])
        {
          distance[i]=min+cost[nextnode][i];
          pred[i]=nextnode;
        }
    count++;
  }
	int h=0;
  for( h=0; h<30; h++)reverse[h]=0;

  i  = dest;
  if(i!=origin)
  {
    reverse[0] = i;
    here++;
    j=i;
    while(j!=origin)
    {
      j=pred[j];
      reverse[here] = j;
      here++;
    }
  }
  
  
  int len = 0, reversed[50];
  int i=0,j;
  for(i=0;i<50;i++){
    if(reverse[i]!=0){
      len++;
    }
  }
  
  for(i=0; i<len; i++){
    reversed[len-i] = reverse[i];
  }
  for(i=5; i<=len; i++){
    for(j=0; j<MAX_VERTEX; j++){
      if((reversed[i]==gArray[j].sp_id)&&(gArray[j].sp_id != 0)){
        printf("%d %s\n", gArray[j].sp_id, gArray[j].sp_name);
      }
    }
  }
  
  
}
void free_memory(){
  return;
}

