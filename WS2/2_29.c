/**
 * Description: The program takes 3 inputs and uses power, absolute, and squareroot func to compute the outputs
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/09/2023
 * Creation date: 02/09/2023
 **/
 
 #include <stdlib.h>
 #include <math.h>
#include <stdio.h>

int main(void){
	double x;
	double y;
	double z;
	
	scanf("%lf %lf %lf", &x, &y, &z);
	
	double result = pow(x,z);
	printf("%0.2lf ", result);
	printf("%0.2lf ", pow(x, pow(y, 2)));
	printf("%0.2lf ", fabs(y));
	printf("%0.2lf \n", sqrt(pow(x*y, z)));
	return 0;
}
