/**
 * Description: The program takes a list of integers as an input and outputs the values below a specified amount.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/16/2023
 * Creation date: 02/16/2023
 **/
 
#include <stdio.h>

int main(void){
	int numOfInt = 0;
	int nums[20];
	
	printf("The first integer indicates the number of elements in the list, and the last integer indicates a threshold.\n");
	printf("Enter a list of integers: ");
	scanf("%d", &numOfInt);
	
	for(int i = 0; i <= numOfInt; i++) {
		scanf("%d", &nums[i]);
	}
	
	for(int i = 0; i < numOfInt; i++) {
		if(nums[i] <= nums[numOfInt]) {
			printf("%d,", nums[i]);
		}
	}
	
	printf("\n");
	return 0;
}
