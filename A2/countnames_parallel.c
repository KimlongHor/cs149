/**
 * Description: This program will get one and more file of names and counts all the individual names in the given files.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 03/03/2023
 * Creation date: 03/03/2023
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>

typedef struct my_data {
  char name[30];
  int count;
} my_data;

 /*
 This function counts the names in a given file.
 Assumption: There are less than 100 unique names in the given file and each name has less than 30 characters.
 Inputs:
 - filename: an array of characters
 - *namecounts: a pointer to the my_data struct
 Return: an integer
 */
int countName(char filename[], struct my_data *namecounts) {
	
	int numOfUniqueNames = 0;
 	char curName[100];
 	bool isExisted = false;
 	int curLineInFile = 0;
 	
 	FILE *fp = fopen(filename, "r");
 	
 	if (fp == NULL) {
 		fprintf(stderr, "range: cannot open file: %s\n", filename);
 		exit(1);
 	}
 	
 	while (fgets(curName, 100, fp) != NULL) {
 		// keeps track of the line we are reading in the file 
 		curLineInFile += 1;
 		
 		// if the current line contains only "\n", skip
 		if (strcmp(curName, "\n") == 0) {
 			fprintf(stderr, "Warning - file %s line %d is empty\n", filename, curLineInFile);
 			continue;
 		}
 		
 		// replace "\n" at the end of the name with "\0"
 		if (curName[strlen(curName) - 1] == '\n') {
 			curName[strlen(curName) - 1] = '\0';
 		}
 		
 		// check if it exists in the names array
 		for (int i = 0; i < numOfUniqueNames; i++) {
 			if (strcmp(namecounts[i].name, curName) == 0) {
 				isExisted = true;
 				namecounts[i].count += 1;
 			}
 		}
 		
 		// if the name does not exist in the array, append it to the array and increment the name count
 		if (isExisted == false) {
 			strcpy(namecounts[numOfUniqueNames].name, curName);
 			namecounts[numOfUniqueNames].count = 1;
 			numOfUniqueNames += 1;
 		}
 		
 		isExisted = false;
 	}
 	
 	fclose(fp);
 	return numOfUniqueNames;
}


 /*
 This function counts the names in one or more files.
 Assumption: There are less than 100 unique names in the given file and each name has less than 30 characters.
 Inputs:
 - argc is the number of parameters
 - argv is the pointer to all parameters.
 Return: an integer
 */
int main (int argc, char **argv) {
	char *curFileName;
	my_data totalnamecounts[100]={{{'\0', 0 }}};
	int totalNumOfUniqueNames = 0;
	int pfds[argc - 1][2];
	int pid = 0;
	
	if (argv == NULL) {
		exit(0);
	}
	
	// this loop is for creating pipes and child processes depending on number of files given in the paramter
	for (int i = 1; i < argc; i++) {
		curFileName = argv[i];
		pipe(pfds[i - 1]);
		pid = fork();
		
		// in child process
		if (pid == 0) {
			my_data namecounts[100]={{{ '\0', 0 }}};
			int numOfUniqueNames = 0;
			
			if (fopen(curFileName, "r") == NULL) {
				fprintf(stderr, "range: cannot open file: %s\n", curFileName);
				
				// Pass information to parent process
				write(pfds[i-1][1], namecounts, sizeof(my_data) * 100);
				write(pfds[i-1][1], &numOfUniqueNames, sizeof(numOfUniqueNames));
				close(pfds[i-1][1]);
				exit(1);
			} else {
				// Find number of unique names in a file and update the namecounts variable
				numOfUniqueNames = countName(curFileName, namecounts);
			
				// Pass information to parent process
				write(pfds[i-1][1], namecounts, sizeof(my_data) * 100);
				write(pfds[i-1][1], &numOfUniqueNames, sizeof(numOfUniqueNames));
				close(pfds[i-1][1]);
				exit(0);
			}
			
		} else if (pid < 0) {
			fprintf(stderr, "Failed to fork");
		}
	}
	
	int pipeCount = 0;
	
	// this loop is for getting the information from child process and update the value in totalnamecounts
	while (wait(NULL) != -1) {
		my_data namecounts[100]={{{ '\0', 0 }}};
		int numOfUniqueNames = 0;
		
		// Read information passed from child process
		read(pfds[pipeCount][0], namecounts, sizeof(my_data) * 100);
		read(pfds[pipeCount][0], &numOfUniqueNames, sizeof(numOfUniqueNames));
		close(pfds[pipeCount][0]);
		
		// loop through number of unique names passed from child process
		for (int j = 0; j < numOfUniqueNames; j++) {
			bool isExisted = false;
			
			// this loop is for checking if the name exist in totalnamecounts
			for (int i = 0; i < totalNumOfUniqueNames; i++) {	
	 			if (strcmp(totalnamecounts[i].name, namecounts[j].name) == 0) {
	 				isExisted = true;
	 				totalnamecounts[i].count += 1;
	 			}
	 		}
	 		
	 		// if the name does not exist in the array, append it to the array and increment the name count
	 		if (isExisted == false) {
	 			strcpy(totalnamecounts[totalNumOfUniqueNames].name, namecounts[j].name);
	 			totalnamecounts[totalNumOfUniqueNames].count = namecounts[j].count;
	 			totalNumOfUniqueNames += 1;
	 		}
		}
		// increment to the next pipe
		pipeCount++;
	}
	
	// print the names and its counts
 	for (int i = 0; i < totalNumOfUniqueNames; i++) {
 		printf("%s : %d\n", totalnamecounts[i].name, totalnamecounts[i].count);
 	}
	
	return 0;
}

