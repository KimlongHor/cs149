/**
 * Description: This program 
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
 	char numOfCommand = 0;
 	int pid = 0;
 	
 	while (fgets(command[numOfCommand], MAX_LENGTH, stdin)) {
 		
 		// replace "\n" at the end of the name with "\0"
 		if (command[numOfCommand][strlen(command[numOfCommand]) - 1] == '\n') {
 			command[numOfCommand][strlen(command[numOfCommand]) - 1] = '\0';
 		}
 		
 		numOfCommand++;
 	}
 	
 	for(int i = 0; i < numOfCommand; i++) {
 		pid = fork();
 		
 		if (pid < 0) {
 			fprintf(stderr, "Failed to fork");
 			exit(1);
 		} else if (pid == 0) {
 			char outputFile[100];
 			char errorFile[100];
 			
 			sprintf(outputFile, "%d.out", getpid());
 			sprintf(errorFile, "%d.out", getpid());
 			
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
 			
 			if(dup2(outputFd, 1) < 0) {
 				perror("Failed dup2 for outputFd");
 				exit(2);
 			}
 			close(outputFd);
 			
 			if(dup2(errorFd, 2) < 0) {
 				perror("Failed dup2 for errorFd");
 				exit(2);
 			}
 			close(errorFd);
 			
 			printf("Starting command %d: child %d pid of parent %d", i, getpid(), getppid());		
 		}
 	}
 	
 	return 0;
 }
