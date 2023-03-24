/**
 * Description: This program takes multiple commands and execute them using execvp in child processes.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 03/21/2023
 * Creation date: 03/21/2023
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
 
 #define MAX_NUM_COMMAND 100
 #define MAX_LENGTH 30
 
 int main(void) {
 	char command[MAX_NUM_COMMAND][MAX_LENGTH];
 	unsigned char numOfCommand = 0;
 	int pid = 0;
 	
 	// This while loop read all command line until control-d and store them in an array
 	while (fgets(command[numOfCommand], MAX_LENGTH, stdin)) {
 		
 		// replace "\n" at the end of the command with "\0"
 		if (command[numOfCommand][strlen(command[numOfCommand]) - 1] == '\n') {
 			command[numOfCommand][strlen(command[numOfCommand]) - 1] = '\0';
 		}
 		
 		numOfCommand++;
 	}
 	
 	// This loops through each command of the array
 	for(int i = 0; i < numOfCommand; i++) {
 	
 		// create a child process
 		pid = fork();
 		
 		if (pid < 0) { // if fork() fails
 			fprintf(stderr, "Failed to fork");
 			exit(1);
 		} else if (pid == 0) { // child process
 			char outputFile[100];
 			char errorFile[100];
 			
 			// set up two file names; one for output and one for error
 			sprintf(outputFile, "%d.out", getpid());
 			sprintf(errorFile, "%d.err", getpid());
 			
 			// create file descriptor for output and error files
 			int outputFd = open(outputFile, O_RDWR | O_CREAT | O_APPEND, 0777);
 			int errorFd = open(errorFile, O_RDWR | O_CREAT | O_APPEND, 0777);
 			
 			if (outputFd < 0) {
 				perror("Failed opening output file.");
 				exit(1);
 			}
 			
 			if (errorFd < 0) {
 				perror("Failed opening error file.");
 				exit(1);
 			}
 			
 			// duplicate outputFd into stdout which is 1
 			if(dup2(outputFd, 1) < 0) {
 				perror("Failed dup2 for outputFd");
 				exit(2);
 			}
 			
 			// duplicate errorFd into stderr which is 2
 			if(dup2(errorFd, 2) < 0) {
 				perror("Failed dup2 for errorFd");
 				exit(2);
 			}
 
 			printf("Starting command %d: child %d pid of parent %d\n", i+1, getpid(), getppid());
 			
 			// clean buffer. Without this, the [pid].out will be overwritten by the execvp result
 			fflush(STDIN_FILENO);
 			
 			close(outputFd);
 			close(errorFd);
 			
 			// set up commands
 			char *arg[MAX_LENGTH];
 			int argCount = 0;
 			arg[argCount] = strtok(command[i], " ");
 			
 			while (arg[argCount] != NULL) {
 				argCount++;
 				arg[argCount] = strtok(NULL, " ");
 			}
 			
 			arg[argCount+1] = NULL;
 			
 			// execute the command using execvp
 			if (execvp(arg[0], arg) < 0) {
 				perror("Failed execvp");
 				exit(2);
 			}
 		}
 	}
 	
 	int status;
 	
 	// In parent process
 	while((pid = wait(&status)) > 0) {
 		char outputFile[100];
		char errorFile[100];
		
		// set up two file names; one for output and one for error
		sprintf(outputFile, "%d.out", pid);
		sprintf(errorFile, "%d.err", pid);
		
		// open both output and error files; "a" is append
		FILE *outFile = fopen(outputFile, "a");
		FILE *errFile = fopen(errorFile, "a");
		
		// write a message into output file
		fprintf(outFile, "Finish child %d pid of parent %d\n", pid, getpid());
		
		// check the status and write a message to error file accordingly
		if (WIFEXITED(status))
        	{
            		fprintf(errFile, "Exited with exitcode = %d", WEXITSTATUS(status));
        	}
		else if (WIFSIGNALED(status))
		{
			fprintf(errFile, "Killed with signal %d", WTERMSIG(status));
		   	
		}
		
		fclose(outFile);
		fclose(errFile);
 	}
 	
 	return 0;
 }
