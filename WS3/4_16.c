/**
 * Description: The program takes any non-negative integers and ouputs the max and average
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/16/2023
 * Creation date: 02/16/2023
 **/
 
#include <stdio.h>

int main(void){
	printf("Enter integers: ");
	int max = 0;
	double sum = 0;
	int count = 0;
	double average = 0;
	int curNum = 0;
	
	// The scanf() function returns the number of fields that were successfully converted and assigned.  
	while(scanf("%d", &curNum)) {
		if (curNum < 0) {
			break;
		} else if (curNum > max){
			max = curNum;
		}
		sum += curNum;
		count++;
	}
	
	average = sum/count;
	
	printf("The max number is: %d\n", max);
	printf("The average is %0.2lf\n", average);
	
	return 0;
}
