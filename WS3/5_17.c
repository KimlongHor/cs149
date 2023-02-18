/**
 * Description: The program takes a sorted list of integers and outputs the middle integer.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/16/2023
 * Creation date: 02/16/2023
 **/
 
#include <stdio.h>

int main(void){
	int count = 0;
	int nums[9];
	int curNum = 0;
	
	printf("Enter a sorted list of integers: ");
	while(scanf("%d", &curNum)) {
		if(curNum < 0) {
			break;
		} else {
			nums[count] = curNum;
		}
		count++;
	}
	
	printf("The middle item: %d\n", nums[count/2]);
	
	return 0;
}
