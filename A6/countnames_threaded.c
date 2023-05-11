/**
 * Description:
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 05/07/2023
 * Creation date: 05/07/2023
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

void* thread_runner(void*);
pthread_t tid1, tid2;

//struct points to the thread that created the object.
//This is useful for you to know which is thread1. Later thread1 will also deallocate.
struct THREADDATA_STRUCT{
	pthread_t creator;
};

typedef struct THREADDATA_STRUCT THREADDATA;
THREADDATA* p=NULL;

//variable for indexing of messages by the logging function.
int logindex=0;
int *logip = &logindex;

struct NAME_STRUCT {
	char name[30];
	int count;
};

typedef struct NAME_STRUCT THREAD_NAME;

//node with name_info for a linked list
typedef struct NAME_NODE {
	THREAD_NAME name_count;
	struct NAME_NODE *next;
} NAME_NODE;

// Define linkedlist struct
typedef struct LinkedList {
	NAME_NODE *head;
} LinkedList;

/*
 This function allocates memory for a new linkedlist
 Assumption: None
 Inputs: None
 Return: a linkedlist pointer
 */
LinkedList* initLinkedList() {
	LinkedList* list = malloc(sizeof(LinkedList));
	list->head = NULL;
	return list;
}

//LinkedList* list = NULL;

NAME_NODE* head = NULL;

/*
 This function frees the allocated memory for a linkedlist
 Assumption: None
 Inputs: a linkedlist pointer
 Return: void
 */
void freeLinkedList(LinkedList* list) {
	NAME_NODE* current = list->head;
	NAME_NODE* next = NULL;
	
	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	
	free(list);
}

/*
 This function prints out the content in a linkedlist recursively
 Assumption: None
 Inputs: a node pointer
 Return: void
 */
void PrintNodes(NAME_NODE *head) {
	if (head == NULL) {
		printf("\n");
		return;
	}
	printf("%s: %d\n", head->name_count.name, head->name_count.count);
	PrintNodes(head->next);
}


/*********************************************************
// function main
*********************************************************/
int main(int argc, char** argv) {

	// check the number of files
	if(argc != 3) {
		perror("You must enter two input files.\n");
		exit(1);
	}
	//list = initLinkedList();
	head = (NAME_NODE*) calloc(1, sizeof(NAME_NODE));
	
	printf("create first thread\n");
	pthread_create(&tid1,NULL,thread_runner, argv[1]);
	
	printf("create second thread\n");
	pthread_create(&tid2,NULL,thread_runner, argv[2]);
	
	printf("wait for first thread to exit\n");
	pthread_join(tid1,NULL);
	printf("first thread exited\n");
	
	printf("wait for second thread to exit\n");
	pthread_join(tid2,NULL);
	printf("second thread exited\n");
	
	//TODO print out the sum variable with the sum of all the numbers
	PrintNodes(head);
	
	//freeLinkedList(list);
	
	exit(0);
}

/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/
void* thread_runner(void* filename) {
	pthread_t me;
	me = pthread_self();
	
	printf("This is thread %ld (p=%p)\n",me,p);
	pthread_mutex_lock(&tlock2); // critical section starts (p)
	
	if (p==NULL) {
		p = (THREADDATA*) malloc(sizeof(THREADDATA));
		p->creator=me;
	}
	pthread_mutex_unlock(&tlock2); // critical section ends (p)
	
	pthread_mutex_lock(&tlock1); // critical section starts (logindex)
	logindex++;
	if (p!=NULL && p->creator==me) {
		printf("Logindex %d, This is thread %ld and I created THREADDATA %p\n",logindex, me,p);
	} else {
		printf("Logindex %d, This is thread %ld and I can access the THREADDATA %p\n",logindex, me,p);
	}
	pthread_mutex_unlock(&tlock1); // critical section ends (logindex)
	
	
	FILE *fp = fopen((char*) filename, "r");
	if (fp == NULL) { // fail
		pthread_mutex_lock(&tlock1); // critical section starts (logindex)
		logindex++;
 		fprintf(stderr, "Logindex %d, range: cannot open file: %s\n", logindex, (char*) filename);
 		pthread_mutex_unlock(&tlock1); // critical section ends (logindex)
 	} else { // success
 		pthread_mutex_lock(&tlock1); // critical section starts (logindex)
 		logindex++;
 		printf("Logindex %d, opened file: %s successfully.\n", logindex, (char*) filename);
 		pthread_mutex_unlock(&tlock1); // critical section ends (logindex)
 		
 		char* input = NULL;
		size_t inputLength = 0;
	 	int curLineInFile = 0;
	 	
	 	// get the input
		while (getline(&input, &inputLength, fp) != -1) {
			bool isExisted = false;
			
			// keeps track of the line we are reading in the file 
 			curLineInFile += 1;
 			
 			if (strcmp(input, "\n") == 0) {
	 			fprintf(stderr, "Warning - file %s line %d is empty\n", (char*) filename, curLineInFile);
	 			continue;
 			}
 			
 			// replace "\n" at the end of the name with "\0"
	 		if (input[strlen(input) - 1] == '\n') {
	 			input[strlen(input) - 1] = '\0';
	 		}
	 		
	 		//NAME_NODE* curNode = list->head;
	 		NAME_NODE* curNode = head;
	 		
	 		
	 		pthread_mutex_lock(&tlock3); // critical section starts (linkedlist)
	 		while((curNode = curNode->next) != NULL) {
	 			// if name exists, update the counter and break.
	 			if (strcmp(curNode->name_count.name, input) == 0) {
	 				isExisted = true;
	 				curNode->name_count.count += 1;
	 				break;
	 			}
	 			//curNode = curNode->next;
	 		}
	 		pthread_mutex_unlock(&tlock3); // critical section ends (linkedlist)
	 		
	 		
	 		if (isExisted == false) {
	 			THREAD_NAME name = {{'\0', 0}};
	 			strcpy(name.name, input);
	 			name.count = 1;
	 			NAME_NODE* newNode = (NAME_NODE*) calloc(1, sizeof(NAME_NODE));
	 			
	 			
	 			pthread_mutex_lock(&tlock3); // critical section starts (linekdlist)
	 			newNode->name_count = name;
	 			newNode->next = head->next;
	 			head->next = newNode;
	 			//NAME_NODE* temp = list->head;
	 			//newNode->next = temp->next;
	 			//temp->next = newNode;
	 			pthread_mutex_unlock(&tlock3); // critical section ends (linkedlist)
	 		}
	 		
		}
		
		free(input);
		fclose(fp);
 	}
	
	pthread_mutex_lock(&tlock2); // critical section starts (p)
	if (p!=NULL && p->creator==me) {
		pthread_mutex_unlock(&tlock2); // critical section ends (p)
		
		pthread_mutex_lock(&tlock1); // critical section starts (logindex)
		logindex++;
		printf("Logindex %d, This is thread %ld and I delete THREADDATA\n",logindex, me);
		pthread_mutex_unlock(&tlock1); // critical section ends (logindex)

		/**
		* TODO Free the THREADATA object.
		* Freeing should be done by the same thread that created it.
		* See how the THREADDATA was created for an example of how this is done.
		*/
		pthread_mutex_lock(&tlock2); // critical section starts (p)
		free((void*)p);
		p = NULL;
		pthread_mutex_unlock(&tlock2); // critical section ends (p)
	} else {
		pthread_mutex_unlock(&tlock2); // critical section ends (p)
		pthread_mutex_lock(&tlock1); // critical section starts (logindex)
		logindex++;
		printf("Logindex %d, This is thread %ld and I can access the THREADDATA\n", logindex, me);
		pthread_mutex_unlock(&tlock1); // critical section ends (logindex)
	}
	
	pthread_exit(NULL);
	return NULL;
}//end thread_runner

