/**
 * Description: The program takes a positive integer and outputs its binary in reverse order.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/16/2023
 * Creation date: 02/16/2023
 **/
 
#include <stdio.h>

int main(void){
	int input;
	printf("Input an integer: ");
	scanf("%d", &input);
	
	while(input > 0) {
		printf("%d", input % 2);
		input = input / 2;
	}
	
	printf("\n");
	return 0;
}
