/**
 * Description: This program takes 4 integers as an input and swap the first input with the second input and the third input with the fourth input.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 03/19/2023
 * Creation date: 03/19/2023
 **/
 
 #include <stdio.h>
 
 /*
 This function swaps the first value with second value and the third value with the fourth value.
 Assumption: None
 Inputs: 4 integers pointers
 Return: Void
 */
 void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4) {
 	int temp = 0;
 	temp = *userVal1;
 	*userVal1 = *userVal2;
 	*userVal2 = temp;
 	
 	temp = *userVal3;
 	*userVal3 = *userVal4;
 	*userVal4 = temp;
 }
 
 int main(void) {
 	int first, second, third, fourth;
 	
 	printf("Input: ");
 	scanf("%d %d %d %d", &first, &second, &third, &fourth);
 	SwapValues(&first, &second, &third, &fourth);
 	printf("Output: %d %d %d %d\n", first, second, third, fourth);
 	return 0;
 }
