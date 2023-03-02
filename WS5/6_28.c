/**
 * Description: This program removes all non-alphabetic character from the given input.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 03/02/2023
 * Creation date: 03/02/2023
 **/
 
#include <stdio.h>
#include <string.h>
#include <ctype.h>

 /*
 This function removes the non-alphabetic character in userString and assigns it to userStringAlphaOnly
 Assumption: the string length of the user's input does not exceed 50.
 Inputs: userString and userStringAlphaOnly
 Return: void
 */
 void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]) {
 	for (int i = 0; i < strlen(userString); i++) {
 		if (isalpha(userString[i])) {
 			strncat(userStringAlphaOnly, &userString[i], 1);
 		}
 	}
 }
 
int main(void){
	char input[50] = "";
	char result[50] = "";
	
	printf("Input: ");
	fgets(input, 50, stdin);
	
	RemoveNonAlpha(input, result);
	printf("Output: %s\n", result);
	return 0;
}
