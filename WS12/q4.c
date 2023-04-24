/**
 * Description: The program allocates memory for an integer, assign a value, and display it.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 04/24/2023
 * Creation date: 04/23/2023
 
 * What happens with the program when run?
 * Answer: 
 * When using gcc the program compiles with no errors or warnings shown
 * Now when the program runs the following output is 
 * The int value is: 1234.
 
 * Is there a problem with Valgrind when running the program?
 * Answer: 
 * When using valgrind it points out that there is a leak that is said "4 bytes definitely lost" showing that it is not freed.
 **/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int* lab = malloc(sizeof(int));
    *lab = 1234;
    printf("The int value is: %d\n", *lab);
}

