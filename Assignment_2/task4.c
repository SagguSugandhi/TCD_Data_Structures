#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define arrayay_end 18625
#define MAX_BUFFER 100

int dEBUG = 0;

typedef struct Game Game;

struct Game {

    char title[MAX_BUFFER],
    platform[MAX_BUFFER];
    int score,
    releaseYear;
};

Game games[arrayay_end];

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

void fetch_Game (FILE *csv, struct Game *g) {
    char buf[MAX_BUFFER];

    next_field(csv, g->title, MAX_BUFFER);

    next_field(csv, g->platform, MAX_BUFFER);

    next_field(csv, buf, MAX_BUFFER);
    g->score = atoi(buf);

    next_field(csv, buf, MAX_BUFFER);
    g->releaseYear = atoi(buf);

}
void print_game( struct Game *g ) {
    printf("  %i %s %s %i\n", g->score, g->title, g->platform, g->releaseYear );

}

void printarrayay(int array[], int end){
    int i;
    for (i=0; i < end; i++)
        printf("%d ", array[i]);
    printf("\n");

}


void swap(int *x,int *y){
    int temp;
    if(*x != *y){ 
        temp = *x;
        *x = *y;
        *y = temp;
        
        if(dEBUG == 1){
            printf("Swapped %d %d \n", *x, *y);
        }
    }
    if(dEBUG == 1){
        printf("No Swapp %d %d \n", *x, *y);
    }

}

int partition (struct Game *arrayay, int start, int end){ 
    int pivot = arrayay[end].score;    // pivot
    int i = (start - 1);  
    for (int j = start; j <= (end - 1); j++){
        
        if (arrayay[j].score <= pivot){
            
            i++;    


            swap(&arrayay[i].score, &arrayay[j].score);

        }

    }

    swap(&arrayay[i + 1].score, &arrayay[end].score); 
    if(dEBUG == 1){
        printf("Inside partition_2");
    }

    return (i+1); 
}
void quicksort(Game *A, int start, int end){

    if (start < end){
        int partition_1 = partition(A, start, end);

        quicksort(A, start, partition_1-1);
        quicksort(A, partition_1+1, end);

    }

}

int main ( int argc, char *argv[] ) {
    FILE *csv;
    Game g;
    int i = 0;

    csv = fopen ("C:/Users/sugandhi saggu/downloads/t4_ign.csv","r");

    if (csv==NULL) {
        perror ("Error opening file");
    }

    fetch_Game(csv, &g);


    while(!feof(csv)){
        fetch_Game(csv, &g);
        games[i] = g;
        i++;
    }

    quicksort(games, 0,(arrayay_end - 1));

    for(int i =arrayay_end-1;i>arrayay_end-11;i--){

         if(games[i].score==10)
        {
         print_game(&games[i]);
        }
    }

    fclose(csv);
    return 0;
}
