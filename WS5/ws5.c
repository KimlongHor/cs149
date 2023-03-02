/**
 * Description: This program uses fork() to print "Hello World".
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 03/02/2023
 * Creation date: 03/02/2023
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
 
int main(void){
	pid_t p;
	p = fork();
	p = fork();
	
	if (p < 0) {
		fprintf(stderr, "fork Failed\n"); 
        	return 1; 
	} else if (p > 0) { // parent
		wait(NULL);
		printf("Hello World from PID %d\n", getpid());
	} else { // child
		printf("Hello World from PID %d\n", getpid());
	}
	
	return 0;
}
