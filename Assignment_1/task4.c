/*
SUGANDHI SAGGU
21355223
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 99991
#define maxStrs 60

int collisions = 0; 
int UnqName = 0; 

struct name{
    int k; 
    char name[maxStrs];
    int freq;
    struct LinkedList* List; 
};

struct LinkedList{
	struct Node * head;
	struct Node * tail;
};

struct Node{
	int age;
	int personId;
	char surname[maxStrs];
	char forename[maxStrs];
	char depositionId[maxStrs];
	char personType[maxStrs];
	char gender[maxStrs];
	char nationality[maxStrs];
	char religion[maxStrs];
	char occupation[maxStrs];

	struct Node * next;
};

struct name * hashTable[N];

void printList(struct LinkedList * list);


void insert(char * surname, char * forename, int id, int age, char * deposition, char * type,char * gender,char * nationality,char * religion,char * occupation);
int next_field(FILE * csv, char * buffer, int length);
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
                printList(item->List);
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
void printList(struct LinkedList * list){
	struct Node * next = list->head;
	printf("%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s\n", "Person ID", "Deposition ID","Surname", "Forename", "Person Age", "Person Type","Gender","Nationality","Religion","Occupation");
	while(next != NULL){
		printf("%20d\t%20s\t%20s\t%20s\t%20d\t%20s\t%20s\t%20s\t%20s\t%20s\n", next->personId, next->depositionId, next->surname, next->forename, next->age, next->personType,next->gender,next->nationality,next->religion,next->occupation);
		next = next->next;
	}
}



int main()
{
    int i,c;
    FILE *f;
    char buf[ maxStrs];
    f = fopen("people.csv", "r");
    if (!f) { 
        printf("Failed \n");
        return 0; 
    }
    while(c != 1){
		c = next_field(f, buf, maxStrs);
	}
    while ( c != -1 ) {
        //next_field(f,buf,maxStrs);
        //insert( buf); 
		
		int id;
		int age;
		char type[maxStrs];
		char surname[maxStrs];
		char forename[maxStrs];
		char deposition[maxStrs];
	
		char gender[maxStrs];
		char nationality[maxStrs];
		char religion[maxStrs];
		char occupation[maxStrs];
		
		c = next_field(f, buf, maxStrs);
		id = atoi(buf);
		c = next_field(f, deposition, maxStrs);
		c = next_field(f, surname, maxStrs);
		c = next_field(f, forename, maxStrs);
		c = next_field(f, buf, maxStrs);
		age = atoi(buf);
		c = next_field(f, type, maxStrs);
		
		c = next_field(f, gender, maxStrs);
		c = next_field(f, nationality, maxStrs);
		c = next_field(f, religion, maxStrs);
		c = next_field(f, occupation, maxStrs);



		insert(surname, forename, id, age, deposition, type,gender,nationality,religion,occupation);
		while(c != 1 && c !=-1){
			c = next_field(f, buf, maxStrs);
		}  
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






void insert(char * surname, char * forename, int id, int age, char * deposition, char * type,char * gender,char * nationality,char * religion,char * occupation){


    int k = hash(surname)%N;
	int i=0;
    while( hashTable[k] != NULL ){ 
        if( strcmp(hashTable[k]->name, surname) == 0 ){
            hashTable[k]->freq++;
            struct Node * node = malloc(sizeof(struct Node));

			node->personId = id;
			node->age = age;
			strcpy(node->surname, surname);
			strcpy(node->forename, forename);
			strcpy(node->depositionId, deposition);
			strcpy(node->personType, type);
			
			strcpy(node->personType, gender);
			strcpy(node->personType, nationality);
			strcpy(node->personType, religion);
			strcpy(node->personType, occupation);

			hashTable[k]->List->tail->next = node;
			hashTable[k]->List->tail = node;
            return;
        }else{
            int old = k;
			k = hash(surname) + ( (++i) * hash3(surname));
			k %= N;
			collisions++;
			if (old ==k)
			{
				printf("Key value didn't change for %s\n", surname);
			}
        }

    }

    UnqName++;

    struct name * element = malloc(sizeof(struct name));
    struct LinkedList * LList = malloc(sizeof(struct LinkedList));
	struct Node * head = malloc(sizeof(struct Node));

	head->personId = id;
	head->age = age;
	strcpy(head->surname, surname);
	strcpy(head->forename, forename);
	strcpy(head->depositionId, deposition);
	strcpy(head->personType, type);
	
	strcpy(head->gender, gender);
			strcpy(head->nationality, nationality);
			strcpy(head->religion, religion);
			strcpy(head->occupation, occupation);

	element->List = LList;
	element->List->head = head;
	element->List->tail = head;

	strcpy(element->name, surname);
	element->freq = 1;

	hashTable[k] = element;
}

int next_field(FILE * csv, char * buffer, int length){ 
    char c = fgetc(csv);
	int i = 0;
	int flag = 0;
 
	while(i<length){
 
		if(c == ',' && !flag){
			break;
		}
		if(c == '\n' || c == EOF ){
			break;
		}
 
 		if(c == '"'){
			flag = !flag;
		}else{
			buffer[i++] = c;
		}
		c = fgetc(csv);
	}
 
	buffer[i] = '\0';
	if(c == EOF) return -1;
	if( c == '\n') return 1;
 
	return 0;
}

struct name * search(char *name){ 


    int k = hash(name)%N;
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
