/**
 * Description: The program reads an integer, a list of words, and a character. It will then output the words which contain the character.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 02/16/2023
 * Creation date: 02/16/2023
 **/
 
#include <stdio.h>
#include <string.h>

int main(void){
	int numOfWord = 0;
	char words[20][10]; // array of 20 strings each of length 10
	char searchCharacter;
	
	printf("Enter an integer, a list of words, and a character: \n");
	scanf("%d", &numOfWord);
	
	for(int i = 0; i < numOfWord; i++) {
		scanf("%s", words[i]);
	}
	
	scanf(" %c", &searchCharacter);
	
	for(int i = 0; i < numOfWord; i++) {
		if (strchr(words[i], searchCharacter) != NULL) {
			printf("%s, ", words[i]);
		}
	}
	printf("\n");
	return 0;
}
