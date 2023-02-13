/**
 * Description: Write a program using integers userNum and x as input, and output userNum divided by x three times.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/09/2023
 * Creation date: 02/09/2023
 **/
 
#include <stdio.h>

int main(void){
	int userNum;
	int x;

	scanf("%d %d", &userNum, &x);
	
	int num1 = userNum/x;
	int num2 = num1/x;
	int num3 = num2/x;

	printf("%d %d %d\n", num1, num2, num3);
	return 0;
}
