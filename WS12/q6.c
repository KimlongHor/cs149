/**
 * Description: 
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 04/24/2023
 * Creation date: 04/23/2023
 
 * What happens with the program when run? 
 * Answer: 
 * When using gcc the program compiles with no errors or warnings shown
 * Now when the program runs the following output is 0
 
 * Is there a problem with Valgrind when running the program?
 * Answer: 
 * When using valgrind it detects an error saying an invalid read when it has been freed and no mem leak
 * What is happening is that it detects when it has been freed telling us that the pointer has become null or 0.
 
 **/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *data = malloc(100 * sizeof(int));
    free(data);

    printf("%d\n", data[50]);
}
