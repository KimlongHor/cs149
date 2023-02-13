/**
 * Description: The program takes two integer inputs, current price and last month's price of a house, and outputs the current price, the difference, and estimated mortgage.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/09/2023
 * Creation date: 02/09/2023
 **/
 
 #include <stdlib.h>
 #include <math.h>
#include <stdio.h>

int main(void){
	int curPrice;
	int prevPrice;
	
	scanf("%d %d", &curPrice, &prevPrice);
	
	double mortgage = (curPrice * 0.051)/12;
	
	printf("This house is $%d. The change is $%d since last month. \nThe estimated monthly mortgage is $%0.6lf\n", curPrice, curPrice - prevPrice, mortgage);
	return 0;
}
