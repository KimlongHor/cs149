/**
 * Description: The program reads a list of integers, and outputs those integers in reverse.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/16/2023
 * Creation date: 02/16/2023
 **/
 
#include <stdio.h>

int main(void){
	int numOfInt = 0;
	int nums[20]; // array of 20 ints
	
	printf("Note: the first number is the number of integers that follow. \n");
	printf("Enter a list of integers: \n"); 
	scanf("%d", &numOfInt);
	
	for (int i = 0; i < numOfInt; i++) {
		scanf("%d", &nums[i]);
	}
	
	for (int i = numOfInt - 1; i >= 0; i--) {
		printf("%d, ", nums[i]);
	}
	
	printf("\n");
	return 0;
}
