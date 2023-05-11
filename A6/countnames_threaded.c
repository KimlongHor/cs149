/**
 * Description: This programs takes 2 input files containing names as an argument, counts them in 2 different thread, and output the result.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 05/10/2023
 * Creation date: 05/07/2023
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

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

static NAME_NODE* head = NULL;
static char* curDateAndTime = NULL;

/*
 This function frees the allocated memory for a linkedlist
 Assumption: None
 Inputs: a node pointer
 Return: void
 */
void freeLinkedList(NAME_NODE* head) {
	NAME_NODE* current = head;
	NAME_NODE* next = NULL;
	
	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
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
	
	printf("======================= Log Messages =======================\n");
	
	// check the number of files
	if(argc != 3) {
		perror("You must enter two input files.\n");
		exit(1);
	}

	head = (NAME_NODE*) calloc(1, sizeof(NAME_NODE));
	curDateAndTime = (char*) malloc(100);
	
	printf("Create first thread\n");
	pthread_create(&tid1,NULL,thread_runner, argv[1]);
	
	printf("Create second thread\n");
	pthread_create(&tid2,NULL,thread_runner, argv[2]);
	
	//printf("wait for first thread to exit\n");
	pthread_join(tid1,NULL);
	printf("First thread exited\n");
	
	//printf("wait for second thread to exit\n");
	pthread_join(tid2,NULL);
	printf("Second thread exited\n");
	
	//print out the sum variable with the sum of all the numbers
	printf("======================= Name counts =======================\n");
	PrintNodes(head->next);
	
	freeLinkedList(head);
	free(curDateAndTime);
	exit(0);
}

/**********************************************************************
// function getCurrentDateAndTime gets current date and time
**********************************************************************/
void getCurrentDateAndTime(char* curDateAndTime) {
	time_t t = time(NULL);
	struct tm *localTime = localtime(&t);
	
	int year, month, day, hour, minute, second;
	year = localTime->tm_year + 1900;
	month = localTime->tm_mon + 1;
	day = localTime->tm_mday;
	hour = localTime->tm_hour;
	minute = localTime->tm_min;
	second = localTime->tm_sec;
	
	if (hour < 12) {
		sprintf(curDateAndTime, "%02d/%02d/%d %02d:%02d:%02d am: ", month, day, year, hour, minute, second);
	} else if (hour == 12) {
		sprintf(curDateAndTime, "%02d/%02d/%d %02d:%02d:%02d pm: ", month, day, year, hour, minute, second);
	} else {
		sprintf(curDateAndTime, "%02d/%02d/%d %02d:%02d:%02d pm: ", month, day, year, hour - 12, minute, second);
	}
} 

/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/
void* thread_runner(void* filename) {
	pthread_t me;
	me = pthread_self();
	
	//printf("This is thread %ld (p=%p)\n",me,p);
	pthread_mutex_lock(&tlock2); // critical section starts (p)
	
	if (p==NULL) {
		p = (THREADDATA*) malloc(sizeof(THREADDATA));
		p->creator=me;
	}
	pthread_mutex_unlock(&tlock2); // critical section ends (p)
	
	getCurrentDateAndTime(curDateAndTime);
	pthread_mutex_lock(&tlock1); // critical section starts (logindex)
	logindex++;
	if (p!=NULL && p->creator==me) {
		printf("Logindex %d, thread %ld, PID %d, %s This is thread %ld and I created THREADDATA %p\n", logindex, me, getpid(), curDateAndTime, me, p);
	} else {
		printf("Logindex %d, thread %ld, PID %d, %s This is thread %ld and I can access the THREADDATA %p\n", logindex, me, getpid(), curDateAndTime, me, p);
	}
	pthread_mutex_unlock(&tlock1); // critical section ends (logindex)
	
	
	getCurrentDateAndTime(curDateAndTime);
	FILE *fp = fopen((char*) filename, "r");
	if (fp == NULL) { // fail
		pthread_mutex_lock(&tlock1); // critical section starts (logindex)
		logindex++;
		printf("Logindex %d, thread %ld, PID %d, %s range: cannot open file: %s\n", logindex, me, getpid(), curDateAndTime, (char*) filename);
		
 		pthread_mutex_unlock(&tlock1); // critical section ends (logindex)
 	} else { // success
 		pthread_mutex_lock(&tlock1); // critical section starts (logindex)
 		logindex++;
 		printf("Logindex %d, thread %ld, PID %d, %s opened file: %s successfully.\n", logindex, me, getpid(), curDateAndTime, (char*) filename);
		
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
	 		
	 		NAME_NODE* curNode = head;
	 		
	 		
	 		pthread_mutex_lock(&tlock3); // critical section starts (linkedlist)
	 		while(curNode != NULL) {
	 			// if name exists, update the counter and break.
	 			if (strcmp(curNode->name_count.name, input) == 0) {
	 				isExisted = true;
	 				curNode->name_count.count += 1;
	 				break;
	 			}
	 			curNode = curNode->next;
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
	 			pthread_mutex_unlock(&tlock3); // critical section ends (linkedlist)
	 		}
	 		
		}
		
		fclose(fp);
 	}
 	
 	pthread_mutex_lock(&tlock1); // critical section starts (logindex)
	logindex++;
	pthread_mutex_unlock(&tlock1); // critical section ends (logindex)
	
	getCurrentDateAndTime(curDateAndTime);
	pthread_mutex_lock(&tlock2); // critical section starts (p)
	if (p!=NULL && p->creator==me) {
		
		printf("Logindex %d, thread %ld, PID %d, %s This is thread %ld and I delete THREADDATA\n", logindex, me, getpid(), curDateAndTime, me);

		/**
		* Free the THREADATA object.
		* Freeing should be done by the same thread that created it.
		* See how the THREADDATA was created for an example of how this is done.
		*/
		free(p);
		p = NULL;
	} else {
		printf("Logindex %d, thread %ld, PID %d, %s This is thread %ld and I can access the THREADDATA\n", logindex, me, getpid(), curDateAndTime, me);
	}
	pthread_mutex_unlock(&tlock2);

	pthread_exit(NULL);
	return NULL;
}//end thread_runner

