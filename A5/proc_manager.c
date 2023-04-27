/**
 * Description: The program takes commands as an input, stores them in a hashtable and an array, and execute them in child processes.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 04/26/2023
 * Creation date: 04/22/2023
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>

struct nlist {
	struct nlist *next;
	struct timespec starttime;
	struct timespec finishtime;
	int index; 
	int pid;
	char *command;
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* This is the hash function: form hash value for string s */
/* You can use a simple hash function: pid % HASHSIZE */
unsigned hash(int pid) {
	unsigned hashval = pid;
	return hashval % HASHSIZE;
}

/* This function look for a node in hashtab */
/* This is traversing the linked list under a slot of the hash table. The array position to look in is returned by the hash function */
struct nlist *lookup(int pid) {
	struct nlist *np;
	for (np = hashtab[hash(pid)]; np != NULL; np = np->next)
	if (np->pid == pid) {
		return np; /* found */
	}
	return NULL; /* not found */
}

/* This function duplicates the string
 Assumption: None
 Inputs: a character pointer
 Return: a character pointer
*/
char *stringdup(char *s) /* make a duplicate of s */
{
	char *p;
	p = (char *) malloc(strlen(s)+1); /* +1 for */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* This insert returns a nlist node. Thus when you call insert in
your main function */
/* you will save the returned nlist node in a variable (mynode).
*/
/* Then you can set the starttime and finishtime from your main
function: */
/* mynode->starttime = starttime; mynode->finishtime = finishtime;
*/
struct nlist *insert(char* command, int pid, int index) {
	struct nlist *np;
	unsigned hashval;
	
	//There are 2 cases:
	if ((np = lookup(pid)) == NULL) { /* case 1: the pid is not
		found, so you have to create it with malloc. Then you want to set
		the pid, command and index */
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->command = stringdup(command)) == NULL)
			return NULL;
		np->pid = pid;
		np->index = index;
		hashval = hash(pid);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else { } /* case 2: the pid is already there in the
	hashslot, i.e. lookup found the pid. In this case you can either
	do nothing, or you may want to set again the command and index
	(depends on your implementation). */
	return np;
}
/*
 This function allocates new memory for a new created array
 Assumption: each command is less than 100 characters
 Inputs: an integer
 Return: a double char pointer
 */
char** initArray(int size) {
	char** a = malloc(size * sizeof(char*));
	for (int i = 0; i < size; i++) {
		a[i] = malloc(100 * sizeof(char));
	}
	return a;
}

 /*
 This function reallocates memory for a bigger size array
 Assumption: each command is less than 100 characters
 Inputs: a double char pointer and an integer
 Return: a double char pointer
 */
char** resize(char** array, int size) {
	array = realloc(array, size * sizeof(char*));
	for (int i = size - 10; i < size; i++) {
		array[i] = malloc(100 * sizeof(char));
	}
	return array;
}

/*
 This function frees the memory of an array
 Assumption: None
 Inputs: a double char pointer and an integer
 Return: void
 */
void freeArray(char** array, int size) {
	for(int i = 0; i < size; i++) {
		free(array[i]);
	}
	free(array);
}

/*
This function redirect outputs for files
Assumption: None
Inputs: an integer
Return: void
*/
void redirectOutputToFiles(int pid) {
	char outputFile[100];
	char errorFile[100];
	
	// set up two file names; one for output and one for error
	sprintf(outputFile, "%d.out", pid);
	sprintf(errorFile, "%d.err", pid);
	
	// create file descriptor for output and error files
	int outputFd = open(outputFile, O_RDWR | O_CREAT | O_APPEND, 0777);
	int errorFd = open(errorFile, O_RDWR | O_CREAT | O_APPEND, 0777);
	
	if (outputFd < 0) {
		perror("Failed opening output file.\n");
		exit(1);
	}
	
	if (errorFd < 0) {
		perror("Failed opening error file.\n");
		exit(1);
	}
	
	// duplicate outputFd into stdout which is 1
	if(dup2(outputFd, 1) < 0) {
		perror("Failed dup2 for outputFd\n");
		exit(2);
	}
	
	// duplicate errorFd into stderr which is 2
	if(dup2(errorFd, 2) < 0) {
		perror("Failed dup2 for errorFd\n");
		exit(2);
	}
}


/*
 This function frees the memory of a hashtable
 Assumption: None
 Inputs: None
 Return: void
 */
void freeHashTable() {
	for (int i = 0; i < HASHSIZE; i++) {
		struct nlist *cur = hashtab[i];
		while(cur != NULL) {			// free the entire hash chain
		    	struct nlist* next = cur->next;
			free(cur->command);
			free(cur);
			cur = next;
		}
		hashtab[i] = NULL;
	}
}

int main(void) {
	char* input = NULL;
	size_t inputLength = 0;
 	unsigned char inputCount = 0;
	
	int allocatedSize = 10;
	char** inputArray = initArray(allocatedSize);
	
	while (getline(&input, &inputLength, stdin) != -1) {
	
		// replace "\n" at the end of the command with "\0"
 		if (input[strlen(input) - 1] == '\n') {
 			input[strlen(input) - 1] = '\0';
 		}
		
		// check if inputArray needs to be resized to get more space
		// Note: always add 10 more space each time the inputArray resizes.
		if (inputCount % 10 == 0 && inputCount != 0) {
			allocatedSize += 10;
			inputArray = resize(inputArray, allocatedSize);
		}
		
		// copy input into the inputArray and the linkedlink
		strcpy(inputArray[inputCount], input);
		
 		inputCount++;
 	}
 	
 	struct nlist *np;
 	pid_t	pid;
 	struct timespec starttime, finishtime;
 	
 	for (int i = 0; i < inputCount; i++) {
 		clock_gettime(CLOCK_MONOTONIC, &starttime);
 		
 		// create a child process
 		pid = fork();
 		
 		if (pid < 0) { // if fork() fails
 			fprintf(stderr, "Failed to fork\n");
 			exit(2);
 		} else if (pid == 0) { // child process
 			redirectOutputToFiles(getpid());
 			printf("Starting command %d: child %d pid of parent %d\n", i+1, getpid(), getppid());
 			
 			// clean buffer. Without this, the [pid].out will be overwritten by the execvp result
 			fflush(STDIN_FILENO);
 			
 			// set up commands
 			char *arg[strlen(inputArray[i]) + 1];
 			int argCount = 0;
 			arg[argCount] = strtok(inputArray[i], " ");
 			
 			while (arg[argCount] != NULL) {
 				argCount++;
 				arg[argCount] = strtok(NULL, " ");
 			}
 			
 			arg[argCount+1] = NULL;
 			
 			// execute the command using execvp
 			if (execvp(arg[0], arg) < 0) {
 				perror("Failed execvp\n");
 				exit(2);
 			}
 			
 		} else if (pid > 0) {  /* parent goes to the next node */ 
 			np = insert(inputArray[i], pid, i + 1);
 			if (np == NULL) {
 				perror("Failed to inserting new node\n");
 			}
 			np->starttime = starttime;
		}
 	}
 	
 	freeArray(inputArray, allocatedSize);
 	
 	int status;
 	
 	// In parent process
 	while((pid = wait(&status)) > 0) {
 		clock_gettime(CLOCK_MONOTONIC, &finishtime);
 		
 		redirectOutputToFiles(pid);
		
		// check the status and write a message to error file accordingly
		if (WIFEXITED(status)) {
            		fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
        	}
		else if (WIFSIGNALED(status)) {
			fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
		}
		
		struct nlist* curNp = lookup(pid);
 		if (curNp == NULL) {
			perror("Failed to inserting new node\n");
		}
		curNp->finishtime = finishtime;
		
		double elapsed = curNp->finishtime.tv_sec - curNp->starttime.tv_sec;
		
		fprintf(stdout, "Finished child %d pid of parent %d\n", pid, getpid());
		fprintf(stdout, "Finished at %ld, runtime duration %.1f\n", curNp->finishtime.tv_sec, elapsed);
		fflush(STDIN_FILENO);
		
		if (elapsed <= 2) {
			fprintf(stderr, "spawning too fast\n");
		} else {
			clock_gettime(CLOCK_MONOTONIC, &starttime);
			// create a child process
	 		pid = fork();
	 		
	 		if (pid < 0) { // if fork() fails
	 			fprintf(stderr, "Failed to fork\n");
	 			exit(2);
	 		} else if (pid == 0) { // child process
	 			redirectOutputToFiles(getpid());
	 			printf("RESTARTING\n");
	 			printf("Starting command %d: child %d pid of parent %d\n", curNp->index, getpid(), getppid());
	 			
	 			// clean buffer. Without this, the [pid].out will be overwritten by the execvp result
	 			fflush(STDIN_FILENO);
	 			
	 			// set up commands
	 			char *arg[strlen(curNp->command) + 1];
	 			int argCount = 0;
	 			arg[argCount] = strtok(curNp->command, " ");
	 			
	 			while (arg[argCount] != NULL) {
	 				argCount++;
	 				arg[argCount] = strtok(NULL, " ");
	 			}
	 			
	 			arg[argCount+1] = NULL;
	 			
	 			// execute the command using execvp
	 			if (execvp(arg[0], arg) < 0) {
	 				perror("Failed execvp\n");
	 				exit(2);
	 			}
	 			
	 		} else if (pid > 0) {  /* parent goes to the next node */ 
	 			curNp = insert(curNp->command, pid, curNp->index);
	 			if (np == NULL) {
	 				perror("Failed to inserting new node\n");
	 			}
	 			curNp->starttime = starttime;
			}
		}
		
 	}
 	
 	freeHashTable();
	return 0;
}
