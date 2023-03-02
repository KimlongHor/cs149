/**
 * Description: This program counts input length without spaces, periods, exclamation points, or commas
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 03/02/2023
 * Creation date: 03/02/2023
 **/
 
#include <stdio.h>
#include <string.h>

 /*
 This function counts input length without spaces, periods, exclamation points, or commas
 Assumption: the string length of the user's input does not exceed 50.
 Inputs: None
 Return: an integer
 */
int main(void){
	char input[50];
	int count = 0;
	
	printf("Input: ");
	fgets(input, 50, stdin);
	
	for (int i = 0; i < strlen(input)-1; i++) {
		printf("HERE %c\n", input[i]);
		if (input[i] == ' ' || input[i] == '.' || input[i] == '!' || input[i] == ',') {
			continue;
		}
		count++;	
	}
	
	printf("Note: the result does not include the number of space, periods, exclamatoin points, or commas.\n");
	printf("The length of the input is: %d\n", count);
	
	return 0;
}
