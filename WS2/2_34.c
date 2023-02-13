/**
 * Description: The program takes a fisrt name as the input and outputs a welcome message
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/09/2023
 * Creation date: 02/09/2023
 **/

#include <stdio.h>

int main(void){
	char userName[50];
	
	scanf("%s", userName);
	printf("Hello %s, and welcome to CS online!\n", userName);
	return 0;
}
