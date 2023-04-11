/**
 * Description: This program takes string commands as an input and store them in a dynamic allocated array and a linkedlist. It also has memory tracing implemented to keep track of allocated and deallocated memory.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 04/10/2023
 * Creation date: 04/08/2023
 **/
 
 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdarg.h>

/**
 * TRACE_NODE_STRUCT is a linked list of
 * pointers to function identifiers
 * TRACE_TOP is the head of the list is the top of the stack
**/
struct TRACE_NODE_STRUCT {
    char* functionid;                // ptr to function identifier (a function name)
    struct TRACE_NODE_STRUCT* next;  // ptr to next frama
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE* TRACE_TOP = NULL;       // ptr to the top of the stack


/* --------------------------------*/
/* function PUSH_TRACE */
/* 
 * The purpose of this stack is to trace the sequence of function calls,
 * just like the stack in your computer would do. 
 * The "global" string denotes the start of the function call trace.
 * The char *p parameter is the name of the new function that is added to the call trace.
 * See the examples of calling PUSH_TRACE and POP_TRACE below
 * in the main, make_extend_array, add_column functions.
**/
void PUSH_TRACE(char* p)          // push p on the stack
{
    TRACE_NODE* tnode;
    static char glob[]="global";
    
    if (TRACE_TOP==NULL) {
        
        // initialize the stack with "global" identifier
        TRACE_TOP=(TRACE_NODE*) malloc(sizeof(TRACE_NODE));
        
        // no recovery needed if allocation failed, this is only
        // used in debugging, not in production
        if (TRACE_TOP==NULL) {
            printf("PUSH_TRACE: memory allocation error\n");
            exit(1);
        }
        
        TRACE_TOP->functionid = glob;
        TRACE_TOP->next=NULL;
    }//if
    
    // create the node for p
    tnode = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));
    
    // no recovery needed if allocation failed, this is only
    // used in debugging, not in production
    if (tnode==NULL) {
        printf("PUSH_TRACE: memory allocation error\n");
        exit(1);
    }//if
    
    tnode->functionid=p;
    tnode->next = TRACE_TOP;  // insert fnode as the first in the list
    TRACE_TOP=tnode;          // point TRACE_TOP to the first node
    
}/*end PUSH_TRACE*/

/* --------------------------------*/
/* function POP_TRACE */
/* Pop a function call from the stack */
void POP_TRACE()    // remove the op of the stack
{
    TRACE_NODE* tnode;
    tnode = TRACE_TOP;
    TRACE_TOP = tnode->next;
    free(tnode);
    
}/*end POP_TRACE*/

/* ---------------------------------------------- */
/* function PRINT_TRACE prints out the sequence of function calls that are on the stack at this instance */
/* For example, it returns a string that looks like: global:funcA:funcB:funcC. */
/* Printing the function call sequence the other way around is also ok: funcC:funcB:funcA:global */
char* PRINT_TRACE()
{
    int depth = 50; //A max of 50 levels in the stack will be combined in a string for printing out.
    int i, length, j;
    TRACE_NODE* tnode;
    static char buf[100];
    
    if (TRACE_TOP==NULL) {     // stack not initialized yet, so we are
        strcpy(buf,"global");   // still in the `global' area
        return buf;
    }
    
    /* peek at the depth(50) top entries on the stack, but do not
     go over 100 chars and do not go over the bottom of the
     stack */
    
    sprintf(buf,"%s",TRACE_TOP->functionid);
    length = strlen(buf);                  // length of the string so far
    for(i=1, tnode=TRACE_TOP->next;
        tnode!=NULL && i < depth;
        i++,tnode=tnode->next) {
        j = strlen(tnode->functionid);             // length of what we want to add
        if (length+j+1 < 100) {              // total length is ok
            sprintf(buf+length,":%s",tnode->functionid);
            length += j+1;
        }else                                // it would be too long
            break;
    }
    return buf;
} /*end PRINT_TRACE*/

// -----------------------------------------
// function REALLOC calls realloc
// This function prints out the info about memory usage.
void* REALLOC(void* p,int t,char* file,int line)
{
    p = realloc(p,t);
    printf("File %s, line %d, function %s reallocated the memory segment at address %p to a new size %d\n", file, line, PRINT_TRACE(), p, t);
    return p;
}

// -------------------------------------------
// function MALLOC calls malloc
// This function prints out the info about memory usage.
void* MALLOC(int t,char* file,int line)
{
    void* p;
    p = malloc(t);
    printf("File %s, line %d, function %s allocated new memory segment at address %p to size %d\n", file, line, PRINT_TRACE(), p, t);
    return p;
}

// ----------------------------------------------
// function FREE calls free
// This function prints info about memory usage.
void FREE(void* p,char* file,int line)
{
    free(p);
    printf("File %s, line %d, function %s deallocated the memory segment at address %p\n", file, line, PRINT_TRACE(), p);
}

#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)

/*<------------------------------------------------------------------------>*/

// Define node structs for linkedlist
typedef struct Node {
    	char* data;
    	int index;
    	struct Node* next;
} Node;

// Define linkedlist struct
typedef struct LinkedList {
	Node *head;
} LinkedList;

 /*
 This function allocates memory for a new linkedlist
 Assumption: None
 Inputs: None
 Return: a linkedlist pointer
 */
LinkedList* initLinkedList() {
	PUSH_TRACE("initLinkedList");
	LinkedList* list = malloc(sizeof(LinkedList));
	list->head = NULL;
	POP_TRACE();
	return list;
}

 /*
 This function allocates new memory for a new linkedlist node
 Assumption: None
 Inputs: a char pointer and an integer
 Return: a node pointer
 */
Node* createNewNode(char* data, int index) {
	PUSH_TRACE("createNewNode");
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->index = index;
	POP_TRACE();
	return node;
}

 /*
 This function frees the allocated memory for a linkedlist
 Assumption: None
 Inputs: a linkedlist pointer
 Return: void
 */
void freeLinkedList(LinkedList* list) {
	PUSH_TRACE("freeLinkedList");
	Node* current = list->head;
	Node* next = NULL;
	
	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	
	free(list);
	POP_TRACE();
}

 /*
 This function prints out the content in a linkedlist recursively
 Assumption: None
 Inputs: a node pointer
 Return: void
 */
void PrintNodes(Node *head) {
	PUSH_TRACE("PrintNodes");
	if (head == NULL) {
		printf("\n");
		return;
	}
	printf("Node #%d -> %s", head->index, head->data);
	PrintNodes(head->next);
	POP_TRACE();
}

 /*
 This function allocates new memory for a new created array
 Assumption: each command is less than 100 characters
 Inputs: an integer
 Return: a double char pointer
 */
char** initArray(int size) {
	PUSH_TRACE("initArray");
	char** a = malloc(size * sizeof(char*));
	for (int i = 0; i < size; i++) {
		a[i] = malloc(100 * sizeof(char));
	}
	POP_TRACE();
	return a;
}

 /*
 This function reallocates memory for a bigger size array
 Assumption: each command is less than 100 characters
 Inputs: a double char pointer and an integer
 Return: a double char pointer
 */
char** resize(char** array, int size) {
	PUSH_TRACE("resize");
	array = realloc(array, size * sizeof(char*));
	for (int i = size - 10; i < size; i++) {
		array[i] = malloc(100 * sizeof(char));
	}
	POP_TRACE();
	return array;
}

 /*
 This function frees the memory of an array
 Assumption: None
 Inputs: a double char pointer and an integer
 Return: void
 */
void freeArray(char** array, int size) {
	PUSH_TRACE("freeArray");
	for(int i = 0; i < size; i++) {
		free(array[i]);
	}
	free(array);
	POP_TRACE();
}

 /*
 This function redirects the output to an output file "memtrace.out"
 Assumption: None
 Inputs: None
 Return: an integer
 */
int dupOutput() {
	PUSH_TRACE("dupOutput");
	char* outputFile = "memtrace.out";
	int outputFd = open(outputFile, O_RDWR | O_CREAT, 0777);
	if (outputFd < 0) {
		perror("Failed opening output file.");
		exit(1);
	}
	
	// duplicate outputFd into stdout which is 1
	if(dup2(outputFd, 1) < 0) {
		perror("Failed dup2 for outputFd");
		exit(2);
	}
	close(outputFd);
	POP_TRACE();
	return 0;
}

int main(void) {
	PUSH_TRACE("main");
	
	// set up output to the memtrace.out file
	if(dupOutput() != 0) {
		exit(1);
	}
	
	char* input = NULL;
	size_t inputLength = 0;
 	unsigned char inputCount = 0;
	
	int allocatedSize = 10;
	char** inputArray = initArray(allocatedSize);
	
	LinkedList *list = initLinkedList();
	Node *currentNode = NULL;
	
	// get the input
	while (getline(&input, &inputLength, stdin) != -1) {
		
		// check if inputArray needs to be resized to get more space
		// Note: always add 10 more space each time the inputArray resizes.
		if (inputCount % 10 == 0 && inputCount != 0) {
			allocatedSize += 10;
			inputArray = resize(inputArray, allocatedSize);
		}
		
		// copy input into the inputArray and the linkedlink
		strcpy(inputArray[inputCount], input);
		if (inputCount == 0) {
			list->head = createNewNode(inputArray[inputCount], inputCount + 1);
			currentNode = list->head;
		} else {
			currentNode->next = createNewNode(inputArray[inputCount], inputCount + 1);
			currentNode = currentNode->next;
		}
 		inputCount++;
 	}
 	
 	free(input);
 	currentNode->next = NULL;
 	currentNode = NULL;
 	
 	PrintNodes(list->head);
 	freeLinkedList(list);
 	
 	freeArray(inputArray, allocatedSize);
	
	POP_TRACE();
	return 0;
}
