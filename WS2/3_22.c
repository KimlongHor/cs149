/**
 * Description: The program takes 3 integers as the inputs and print the smallest value.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/09/2023
 * Creation date: 02/09/2023
 **/
 
#include <stdio.h>

int main(void){
	int x;
	int y;
	int z;
	scanf("%d %d %d", &x, &y, &z);
	
	if (x < y && x < z) {
		printf("%d\n", x);
	} else if (y < x && y < z) {
		printf("%d\n", y);
	} else {
		printf("%d\n", z);
	}
	
	return 0;
}
