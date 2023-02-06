/**
 * Description: This program takes inputs from the user and do some calculations.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/06/2023
 * Creation date: 02/04/2023
 **/
 
#include <stdio.h>

int main(void){
	int userNum;
	int userNum2;
	
	printf("Enter integer:\n");
	scanf("%d", &userNum);
	
	printf("You entered: %d\n", userNum);
	printf("%d squared is %d\n", userNum, userNum * userNum);
	printf("And %d cubed is %d!!\n", userNum, userNum * userNum * userNum);
	
	printf("Enter another integer:\n");
	scanf("%d", &userNum2);
	
	printf("%d + %d is %d\n", userNum, userNum2, userNum + userNum2);
	printf("%d * %d is %d\n", userNum, userNum2, userNum * userNum2);
	return 0;
}
