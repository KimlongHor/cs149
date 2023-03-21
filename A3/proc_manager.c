/**
 * Description: This program 
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 03/21/2023
 * Creation date: 03/21/2023
 **/
 
 #include <stdio.h>
 #include <string.h>
 
 #define MAX_NUM_COMMAND 100
 #define MAX_LENGTH 30
 
 int main(void) {
 	char command[MAX_NUM_COMMAND][MAX_LENGTH];
 	char numOfCommand = 0;
 	
 	while (fgets(command[numOfCommand], MAX_LENGTH, stdin)) {
 		
 		// replace "\n" at the end of the name with "\0"
 		if (command[numOfCommand][strlen(command[numOfCommand]) - 1] == '\n') {
 			command[numOfCommand][strlen(command[numOfCommand]) - 1] = '\0';
 		}
 		
 		numOfCommand++;
 	}
 	
 	for(int i = 0; i < numOfCommand; i++) {
 		printf("%s\n", command[i]);
 	}
 	
 	return 0;
 }
