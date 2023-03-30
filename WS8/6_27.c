/**
 * Description: This program takes a character and a string as inputs and outputs the number of times the character appears in the given string.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 03/30/2023
 * Creation date: 03/30/2023
 **/
 
 #include <stdio.h>
 #include <string.h>
 
  /*
 This function counts the number of the given character appears in the string
 Assumption: None
 Inputs: a character and a string
 Return: number of the given character appears in the string
 */
 int countNumOfChar(char c, char* s) {
 	int counter = 0;
 	for (int i = 0; i < strlen(s); i++) {
 		if (c == s[i]) {
 			counter++;
 		}
 	}
 	return counter;
 }
 
 int main(void) {
 	char inputChar;
 	char inputString[50];
 	int result = 0;
 	
 	printf("Enter your inputs: ");
 	scanf("%c %s", &inputChar, inputString);
 	
 	result = countNumOfChar(inputChar, inputString);
 	if (result == 1) {
 		printf("%d %c\n", result, inputChar);
 	} else {
 		printf("%d %c's\n", result, inputChar);
 	}
 	
	return 0;
 }
