/**
 * Description: The program takes a double as a parameter, representing the number of laps, and return a double representing the number of miles.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/26/2023
 * Creation date: 02/26/2023
 **/
 
#include <stdio.h>

 /*
 This function coverts number of laps to number of miles.
 Assumption: 1 lap = 0.25 miles
 Inputs:
 - userLaps is the number of laps
 Return: a double
 */
double lapsToMiles(double userLaps) {
	return userLaps * 0.25;
}

int main(void){
	double numOfLaps = 0;
	double numOfMiles = 0;
	printf("Enter number of laps: ");
	scanf("%lf", &numOfLaps);
	
	numOfMiles = lapsToMiles(numOfLaps);
	printf("It is %0.2lf miles\n", numOfMiles);
	return 0;
}
