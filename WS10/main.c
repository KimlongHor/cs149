/**
 * Description: This program prompt the user about the info for two items and outputs the total price.
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 04/09/2023
 * Creation date: 04/08/2023
 **/
 
 #include <stdio.h>
 #include <string.h>
 #include "ItemToPurchase.h"
 
 int main(void) {
 	ItemToPurchase item1;
 	
 	printf("Item 1\n");
 	printf("Enter the item name:\n");
	fgets(item1.itemName, sizeof(item1.itemName), stdin);
	// replace "\n" at the end of the name with "\0"
	if (item1.itemName[strlen(item1.itemName) - 1] == '\n') {
		item1.itemName[strlen(item1.itemName) - 1] = '\0';
	}
 	
 	printf("Enter the item price:\n");
 	scanf("%d", &item1.itemPrice);
 	
 	printf("Enter the item quantity:\n");
 	scanf("%d", &item1.itemQuantity);
 	
 	char c = getchar();
 	while(c != '\n' && c != EOF) {
 		c = getchar();
 	}
 	
 	ItemToPurchase item2;
 	
 	printf("\nItem 2\n");
 	printf("Enter the item name:\n");
	fgets(item2.itemName, sizeof(item2.itemName), stdin);
	
	// replace "\n" at the end of the name with "\0"
	if (item2.itemName[strlen(item2.itemName) - 1] == '\n') {
		item2.itemName[strlen(item2.itemName) - 1] = '\0';
	}
 	
 	printf("Enter the item price:\n");
 	scanf("%d", &item2.itemPrice);
 	
 	printf("Enter the item quantity:\n");
 	scanf("%d", &item2.itemQuantity);
 	
 	printf("\nTOTAL COST\n");
 	PrintItemCost(item1);
 	PrintItemCost(item2);
 	int totalCost = item1.itemPrice * item1.itemQuantity + item2.itemPrice * item2.itemQuantity;
 	printf("\nTotal: $%d\n", totalCost);
 	
 	return 0;
 }
