/**
 * Description: The program takes 4 integers as inputs and outputs the maximum and the minimum of the four values.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/26/2023
 * Creation date: 02/26/2023
 **/
 
#include <stdio.h>

/*
 This function finds maximum number
 Assumption: None
 Inputs:
 - num1 num2 num3 and num4 are all integers
 Return: a integer
 */
int MaxNumber(int num1, int num2, int num3, int num4) {
	int max = num1; 
    
	if (num2 > max) {max = num2;} 
   	if (num3 > max) {max = num3;} 
    	if (num4 > max) {max = num4;} 
    	
    	return max; 
}

/*
 This function finds minimum number
 Assumption: None
 Inputs:
 - num1 num2 num3 and num4 are all integers
 Return: a integer
 */
int MinNumber(int num1, int num2, int num3, int num4) {
	int min = num1; 
    
    	if (num2 < min) {min = num2;} 
    	if (num3 < min) {min = num3;} 
    	if (num4 < min) {min = num4;}
    	
    	return min; 
}

int main(void){
	int num1 = 0;
	int num2 = 0;
	int num3 = 0;
	int num4 = 0;
	
	printf("Enter four integers: ");
	scanf("%d %d %d %d", &num1, &num2, &num3, &num4);
	
	printf("Maximum is %d\n", MaxNumber(num1, num2, num3, num4));
	printf("Minimum is %d\n", MinNumber(num1, num2, num3, num4));
		
	return 0;
}
