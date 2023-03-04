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

void countName(char filename[]) {
	my_data namecounts[100]={ { '\0', 0 } };
	char names[100][30] = {0};
 	int numOfUniqueNames = 0;
 	int nameCounts[100] = {0};
 	char curName[100];
 	bool isExisted = false;
 	int curLineInFile = 0;
 	
 	FILE *fp = fopen(filename, "r");
 	
 	if (fp == NULL) {
 		printf("Cannot open file.\n");
 		exit(1);
 	}
 	
 	while (fgets(curName, 100, fp) != NULL) {
 		// keeps track of the line we are reading in the file 
 		curLineInFile += 1;
 		
 		// if the current line contains only "\n", skip
 		if (strcmp(curName, "\n") == 0) {
 			fprintf(stderr, "Warning - Line %d is empty\n", curLineInFile);
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
 	
 	// print the names and its counts
 	for (int i = 0; i < numOfUniqueNames; i++) {
 		printf("%s : %d\n", namecounts[i].name, namecounts[i].count);
 	}
 	
 	fclose(fp);
}

int main (int argc, char **argv) {
	char *curFileName;
	my_data namecounts[100]={ { '\0', 0 } };
	
	
	for (int i = 1; i < argc; i++) {
		printf("Filename: %s\n", argv[i]);
		curFileName = argv[i];
		int childid = fork();
		if (childid == 0) {
			printf("Current PID: %d\n", getpid());
			countName(curFileName);
			exit(0);
		} else if (childid > 0){
			wait(NULL);
		}
	}
	
	return 0;
}

/*
Plan: 
- Use pipe to pass namecounts from child to parent.
- Find a way to check if all childs check each file concurrently.
*/

