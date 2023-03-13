/**
 * Description: This program take strings as input and print them in reverse order.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 03/13/2023
 * Creation date: 03/13/202
 **/
 
 #include <stdio.h>
 #include <string.h>
 #include <stdbool.h>
 
  /*
 This function reverses a string
 Assumption: None
 Inputs: a string pointer
 Return: None
 */
 void reverseStr(char *input) {
 	int temp;
 	int length = strlen(input);
 	
 	for (int i = 0; i < length/2; i++) {
 		temp = input[i];
 		input[i] = input[length - i - 1];
 		input[length - i - 1] = temp;
 	}
 }
 
 int main(void){
 	char input[50] = "";
 	printf("Enter your input: \n");
 	
 	while(true) {
	 	fgets(input, 50, stdin);
	 	
	 	// replace "\n" at the end of the name with "\0"
 		if (input[strlen(input) - 1] == '\n') {
 			input[strlen(input) - 1] = '\0';
 		}
 		
	 	if (strcmp(input, "Done") == 0 || strcmp(input, "done") == 0 || strcmp(input, "d") == 0) {break;}
	 	
	 	reverseStr(input);
	 	printf("%s \n", input);
 	}
 	
	return 0;
}
