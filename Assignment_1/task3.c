/*
SUGANDHI SAGGU
21355223
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 71
#define maxStrs 30

int collisions = 0; 
int UnqName = 0; 

struct name{
    int k; 
    char name[maxStrs];
    int freq;
};

struct name * hashTable[N];




void insert(char * name);
int next_token(FILE * csv, char * buffer, int length);
struct name * search(char *name);


unsigned int hash3(char* s){
int hash = 0;
while(*s){
hash = 1+ (hash + *s) % (N-1);
s++;
}
return hash;
}
unsigned int hash(char* s)
{
    int hash = 0; 
    int i=2;
    while(*s){ 
        hash = (hash + *s) % (N); 
        s++; 
    }
    return hash;
}

int func(char *input)
{
    while(1){
    int flag=0;
        scanf("%s", input);

        if(strcmp(input, "exit")==0){
            flag= 1;
            return flag;
        }
        else{
            struct name * item = search(input);
            if(item != NULL){
                printf("%s - %d \n", item->name, item->freq);
            }else{
                printf("%s - 0 \n", input);
            }
        }
    }
}

double load(int UnqName)
{
    
    return ((float)UnqName/N);
}
int main()
{
    int i;
    FILE *f;
    char buf[ maxStrs];
    f = fopen("names.csv", "r");
    if (!f) { 
        printf("Failed \n");
        return 0; 
    }
    while ( !feof(f) ) {
        next_token(f,buf,maxStrs);
        insert( buf);   
    }

    fclose(f);
    
    for(i=0; i<=20; i++){
        printf("-");
    }
    printf(" \nCapacity: %d\n", N);
    printf(" Num Terms: %d\n", UnqName);
    printf(" Collisions: %d\n", collisions);
    printf(" Load: %f\n", load(UnqName));
   for(i=0; i<=20; i++){
        printf("-");
    }
    printf("\nEnter name :");
    char input[maxStrs];


        int flag = func(input);
        if(flag==1)
        {
            return 1;
        }

    

    return 0;
}






void insert(char * name){


    int k = hash(name);
int i=0;
    while( hashTable[k] != NULL ){ 
        if( strcmp(hashTable[k]->name, name) == 0 ){
            hashTable[k]->freq++;
            return;
        }else{
            collisions++;
        }
        k = hash(name)+ ((++i)*hash3(name));
        k %= N; 
    }

    UnqName++;

    struct name * element = malloc(sizeof(struct name));
    strcpy(element->name, name);
    element->k = k;
    element->freq = 1;
    hashTable[k] = element;
}

int next_token(FILE * csv, char * buffer, int length){ 
    char c = fgetc(csv);
    int i = 0;
    int flag = 0;

    for(i=0;i<length;i++){

        if(c == ','){
            if(flag==0)
            {
                break;
            }
        }
        if(c == '"'){
            if( flag == 0)
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
        }
        if(c == '\n'){
            break;
        }
        else if(feof(csv))
        {
            break;
        }

        buffer[i] = c;
        c = fgetc(csv);
    }

    buffer[i] = '\0';
    if(c == EOF) return 1;

    return 0;
}

struct name * search(char *name){ 


    int k = hash(name);
	int i=0;
    while( hashTable[k] != NULL ){ 
        if( strcmp(hashTable[k]->name, name) == 0 ){
            return hashTable[k]; 
        }
        k = hash(name) + ((++i)*hash3(name));
        k %= N;

    }

    return NULL;
}
