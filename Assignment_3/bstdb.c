#include "bstdb.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct Node Node;
struct Node{
    char * title;
    int words;
	int height;
	int userid;
    struct Node * left;
    struct Node * right;
    struct Node * parent;

};
Node * root ;
bool duplicate[200000] = {false};
bool isbalanced;
int insertions, traverses;
bool balanced(Node * root);
int gen_id();
Node * tree_insert(Node * r, char* name, int word_count, int userid);
Node * tree_search(Node * r, int doc_id);
void tree_delete (Node * root );
Node* leftmost(Node* root);

int
bstdb_init ( void ) {

	printf("\nIn initialize\n");
	root = (Node*)malloc(sizeof(Node));
	root->height = 1;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	root->title = NULL;
	// root = NULL;
	isbalanced = true;
	insertions = 0;
	traverses = 0;

	return 1;
}

int
bstdb_add ( char *name, int word_count ) {

	 int userid = gen_id();
	
	
	Node *temp = (Node*)malloc(sizeof(Node));
	Node *temp2 ;
	root = tree_insert(root,name,word_count,userid);
	temp2 = root;
	
	
	if (temp == NULL){
		printf("something seems to have gone wrong.");
		return -1;
	}
	return userid;
}

int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	Node *temp = NULL;
    
	temp = tree_search(root,doc_id);
	if (temp == NULL){
		return -1;
	}
	return temp->words;
}

char*
bstdb_get_name ( int doc_id ) {
	
	Node *temp = NULL;
    
	temp = tree_search(root,doc_id);
	if (temp == NULL){
		return NULL;
	}
	return temp->title;
}

void
bstdb_stat ( void ) {

	bool checkbal = balanced(root);
	if (checkbal){
		printf("\nthe tree is balanced");
	 }
	else 
		printf("\n the tree is not balanced");
	
	printf("\nthere were  %d insertions\n", insertions);
	
	float avgnodes = (float)traverses / (float)insertions;
	printf("\nof %d total traversals there were  %f average travrsals for search\n",traverses, avgnodes);
	Node *temp = NULL;
	temp = leftmost(root);
	printf( " the depth of the leftmost root was %d and the root is %d\n", temp->height, root->height);

}

void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	tree_delete(root);
}

Node* tree_search(Node* r, int doc_id){
	Node *temp = NULL;
	if (r == NULL) return temp;
	

	if (r->userid == doc_id){
		traverses++;
		return r;
	}
	else if (r->userid > doc_id){
		traverses++;
		temp = tree_search(r->left,doc_id);
	}
	else{
		traverses++;
		temp = tree_search(r->right,doc_id);
	}
	return temp;

}

int height(Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 

void tree_delete (Node* root ){
    Node *del = (Node*)malloc(sizeof(Node));
    del = root;
    if (del == NULL){
        return;  //if NULL go back to func
    }

    tree_delete(del->left); // delete recurse left goes to leftmost and deletes it
    tree_delete(del->right);   // delete recurse right deletes  any right subtrees

    //deletes current node which now only has null children
    free(del);
}

int max(int a, int b) 
{ 
    if (a > b){
		return a;
	}  
	else return b; 
} 


Node *rightRotate( Node *y) { 
    Node *x = y->left; 
    Node *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
	y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
    // Return new root 
    return x; 
} 

Node *leftRotate( Node *x) { 
    Node *y = x->right; 
    Node *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    // Update heights 
	x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    // Return new root 
    return y; 
} 
bool balanced(Node* r){
	Node *temp = (Node*)malloc(sizeof(Node));
    temp = r;
	int balance;
    if (temp == NULL){ //if NULL go back to func
        return false;
    }
    //recurses on left child
    balanced(temp->left);

    if (temp != NULL){  // if node is not NULL checks balance of children
        
		if (temp == NULL)
			balance = 0;
		else
			balance = height(temp->left) - height(temp->right);
		if ((balance > 1) || (balance < -1))
			isbalanced = false;
    }
    //recurses on right child
    balanced(temp->right);
	if (isbalanced){
		return true;
	}
	else 
		return false;
}



Node * tree_insert(Node* r, char* name, int word_count, int userid){
	
    
	Node *temp ;
	temp = (Node*)malloc(sizeof(Node));
	temp = r;
	if (temp == NULL){	
		Node *temp = (Node*)malloc(sizeof(Node));
		temp->userid = userid;
		temp->right = NULL;
		temp->left = NULL;
		temp->parent = NULL;
		temp->height = 1;
		temp->title = calloc(strlen(name) + 1, sizeof(char));
		if (temp->title)
			strcpy(temp->title , name);
		else{
			Node *del = (Node*)malloc(sizeof(Node));
			del = temp;
			free(del);
			printf("\ndeleted\n");
			temp = NULL;
		}
		temp->words = word_count;
		insertions++;
		return temp;
	}

	if (userid < temp->userid){
		temp->left = tree_insert(temp->left,name, word_count, userid);
	}
	else if(userid > temp->userid){
		temp->right = tree_insert(temp->right,name, word_count, userid);
	}
	else
		return temp;

	 // Update height of  ancestor node 
	if (height(temp->left) > height(temp->right)){
    	temp->height = 1 + height(temp->left);
	}
	else
		temp->height = 1 + height(temp->right);

	
	int balance;
	if (temp == NULL)
		balance = 0;
	else
		balance = height(temp->left) - height(temp->right);

	// If unbalanced, then there are 4 cases 
    // Left Left Case 
    if ((balance > 1) && (userid < temp->left->userid)) 
        return rightRotate(temp); 
  
    // Right Right Case 
    if ((balance < -1) && userid > (temp->right->userid)) 
        return leftRotate(temp); 
  
    // Left Right Case 
    if ((balance > 1) && (userid > temp->left->userid)) 
    { 
        temp->left =  leftRotate(temp->left); 
        return rightRotate(temp); 
    } 
  
    // Right Left Case 
    if ((balance < -1) && (userid < temp->right->userid)) 
    { 
        temp->right = rightRotate(temp->right); 
        return leftRotate(temp); 
    } 
  
    // return the (unchanged) node pointer 
    return temp; 
	
	

}

int gen_id(){
	static int count= 0;
	
	count++;
	return count;

	
	


}
Node* leftmost(Node* root){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp = root;
    while (temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}