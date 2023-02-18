/**
 * Description: The program gets a list of integers. First input indicates the number of integers that follow. The list is followed by two more integers indicating lower and upper bounds of a range. The program will print all integers that are within the range.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/16/2023
 * Creation date: 02/16/2023
 **/
 
#include <stdio.h>

int main(void){
	int numOfInt = 0;
	int nums[20];
	int lowerBound = 0;
	int upperBound = 0;
	
	printf("Enter a list of integers: ");
	scanf("%d", &numOfInt);
	
	for (int i = 0; i < numOfInt; i++) {
		scanf("%d", &nums[i]);
	}
	
	printf("Enter lower and upper bounds: ");
	scanf("%d %d", &lowerBound, &upperBound);
	
	printf("Output: ");
	for (int i = 0; i < numOfInt; i++) {
		if (nums[i] >= lowerBound && nums[i] <= upperBound) {
			printf("%d, ", nums[i]);
		}
	}
	
	printf("\n");
	return 0;
}
