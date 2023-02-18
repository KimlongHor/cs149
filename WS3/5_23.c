/**
 * Description: The program takes a list of integers as an input and outputs the smallest two integers in ascending order.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/16/2023
 * Creation date: 02/16/2023
 **/
 
#include <stdio.h>
#include <limits.h>

int main(void){
	int numOfInt = 0;
	int nums[20];
	
	int min = 0;
	int secMin = INT_MAX;
	
	printf("Note the first integer indicate the number of integers that follow. \n");
	printf("Intput: ");
	scanf("%d", &numOfInt);
	
	for (int i = 0; i < numOfInt; i++) {
		scanf("%d", &nums[i]);
	}
	
	// finding the two smallest
	min = nums[0];
	for (int i = 0; i < numOfInt; i++) {
		if (nums[i] < min) {
			secMin = min;
			min = nums[i];
		} else if (nums[i] > min && nums[i] < secMin) {
			secMin = nums[i];
		}
	}
	
	if (secMin == INT_MAX) {
		printf("The only smallest number is %d.\n", min);
	} else {
		printf("The smallest number is %d.\nThe second smallest number is %d.\n", min, secMin);
	}
	return 0;
}
