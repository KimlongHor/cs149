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
