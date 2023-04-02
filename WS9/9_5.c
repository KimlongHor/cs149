/**
 * Description: This program takes a string with a comma as an input and outputs two words.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 04/01/2023
 * Creation date: 04/01/2023
 **/
 #include <stdio.h>
 #include <stdbool.h>
 #include <string.h>

 /*
 This function checks if a string contains a comma
 Assumption: None
 Inputs: a string
 Return: a boolean
 */
 bool hasComma(char str[]) {
 	for(int i = 0; i < strlen(str); i++) {
 		if (str[i] == ',') {
 			return true;
 		}
 	}
 	return false;
 }
 
  /*
 This function removes spaces in a string
 Assumption: None
 Inputs: a character pointer
 Return: void
 */
 void removeSpace(char* str) {
 	char* temp = str;
 	do {
 		while (*temp == ' '){
 			temp++;
 		}
 	} while(*str++ = *temp++);
 }
 
 int main(void) {
 	char input[50];
 	char *firstWord;
 	char *secondWord;
 	bool quit = false;
 	
 	while(quit == false) {
 		printf("Enter input string: \n");
 		fgets(input, 50, stdin);
 		
 		// replace "\n" at the end of the name with "\0"
 		if (input[strlen(input) - 1] == '\n') {
 			input[strlen(input) - 1] = '\0';
 		}
 		
 		// Check if the user want to quit
 		if (strcmp(input, "q") == 0) {
 			quit = true;
 			break;
 		}
 		
 		// Check if the input string has a comma
 		if (hasComma(input) == false) {
 			printf("Error: No comma in string.\n\n");
 			continue;
 		} 
 		
 		// split the input by the comma
 		char *pt = strtok(input, ",");
 		removeSpace(pt);
 		firstWord = pt;
 		printf("First word: %s\n", firstWord);
 		
 		// move to the word after the comma
 		pt = strtok(NULL, ",");
 		removeSpace(pt);
 		secondWord = pt;
 		printf("Second word: %s\n\n", secondWord);
 	}
 	
 	return 0;
 }
