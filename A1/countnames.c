/**
 * Description: This program will get a file of names and counts all the individual names in the given file.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/19/2023
 * Creation date: 02/19/2023
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
 
 /*
 parameters:
 - argc is the number of parameters
 - argv is the pointer to all parameters.
 */
 int main(int argc, char **argv) {
 	char names[100][30] = {0};
 	int numOfUniqueNames = 0;
 	int nameCounts[100] = {0};
 	char curName[100];
 	bool isExisted = false;
 	int curLineInFile = 0;
 	
 	// In this case, argv[1] = "names.txt"
 	FILE *fp = fopen(argv[1], "r");
 	
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
 			if (strcmp(names[i], curName) == 0) {
 				isExisted = true;
 				nameCounts[i] += 1;
 			}
 		}
 		
 		// if the name does not exist in the array, append it to the array and increment the name count
 		if (isExisted == false) {
 			strcpy(names[numOfUniqueNames], curName);
 			nameCounts[numOfUniqueNames] = 1;
 			numOfUniqueNames += 1;
 		}
 		
 		isExisted = false;
 	}
 	
 	for (int i = 0; i < numOfUniqueNames; i++) {
 		printf("%s : %d\n", names[i], nameCounts[i]);
 	}
 	
 	fclose(fp);
 	
 	return 0;
 }
