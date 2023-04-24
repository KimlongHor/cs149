/**
 * Description: Write a program that creates an array of integers called data of size 100 using malloc, Then set data[100] to 0
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 04/24/2023
 * Creation date: 04/23/2023
 
 * What happens with the program when run?
 * Answer: 
 * When using gcc the program compiles with no errors or warnings shown
 * Now when the program runs the following output is 
 * The value for data[100] = 0.
 
 * Is there a problem with Valgrind when running the program?
 * Answer: 
 * When using valgrind it points out there are errors in the array. It displays "Invalid write of size 4". Also, it shows there are 400 bytes of definately lost memory after the program ends.
 
 * Is the program correct? 
 *Answer: 
 *The program I would say is somewhat correct because it does set the data to 0 
 *but if we want to perform at a higher level of coding standard we would
 *want to free so that the issue of memory being overwritten is not a problem.
 **/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *data = malloc(100*sizeof(int));
    data[100] = 0;

    printf("The value for data[100] = %d\n", data[100]);
}

