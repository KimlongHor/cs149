/**
 * Description: This program takes an array of integers as an input and outputs whether the array contains all multiple of 10, no multiple of 10, or mixd values.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 03/13/2023
 * Creation date: 03/13/202
 **/
 
 #include <stdio.h>
 #include <stdbool.h>
 
 #define MAX_SIZE 20
 
 /*
 This function checks if an array is multiple of 10
 Assumption: None
 Inputs: an array of integers and its size
 Return: boolean value
 */
 bool IsArrayMult10(int inputVals[], int numVals) {
 	bool result = true;
 	for (int i = 0; i < numVals; i++) {
 		if (inputVals[i]%10 != 0) {
 			result = false;
 			break;
 		}
 	}
 	
 	return result;
 }
 
 /*
 This function checks if an array is not multiple of 10
 Assumption: None
 Inputs: an array of integers and its size
 Return: boolean value
 */
 bool IsArrayNoMult10(int inputVals[], int numVals) {
 	bool result = true;
 	for (int i = 0; i < numVals; i++) {
 		if (inputVals[i]%10 == 0) {
 			result = false;
 			break;
 		}
 	}
 	
 	return result;
 }
 
 int main(void) {
 	int input[MAX_SIZE];
 	int size;
 	bool isAllMult10;
 	bool isNoMult10;
 	
 	printf("Enter your input: \n");
 	scanf("%d", &size);
 	
 	for(int i = 0; i < size; i++) {
 		scanf("%d", &input[i]);
 	}
 	
 	isAllMult10 = IsArrayMult10(input, size);
 	isNoMult10 = IsArrayNoMult10(input, size);
 	
 	if(isAllMult10) {
 		printf("all multiple of 10\n");
 	} else if(isNoMult10) {
 		printf("no multiple of 10\n");
 	} else {
 		printf("mixed values\n");
 	}
 	return 0;
 }
