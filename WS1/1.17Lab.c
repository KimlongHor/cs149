/**
 * Description: This program prints an arrow image based on two integers.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/06/2023
 * Creation date: 02/04/2023
 **/
 
#include <stdio.h>

int main(void){
	int baseInt = 0; // default value
	int headInt = 1; // default value
	
	printf("Enter baseInt: ");
	scanf("%d", &baseInt);
	
	printf("Enter headInt: ");
	scanf("%d", &headInt);
	
	printf("Output: \n");
	printf("    %d\n",headInt);
	printf("    %d%d\n",headInt, headInt);
	printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
	printf("%d%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt, headInt);
	printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
	printf("    %d%d\n",headInt, headInt);
	printf("    %d\n",headInt);
	return 0;
}
