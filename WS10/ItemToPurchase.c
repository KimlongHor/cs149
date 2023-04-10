/**
 * Description: Implement functions in ItemToPurchase.h file
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 04/09/2023
 * Creation date: 04/08/2023
 **/
#include <stdio.h>
#include <string.h>
#include "ItemToPurchase.h"

void MakeItemBlank(ItemToPurchase *resetItem) {

    strcpy(resetItem -> itemName, "none");
    resetItem -> itemPrice = 0;
    resetItem -> itemQuantity = 0;
}

void PrintItemCost(ItemToPurchase printItem) {
   printf("%s %d @ $%d = $%d\n", printItem.itemName, printItem.itemQuantity, printItem.itemPrice, printItem.itemPrice * printItem.itemQuantity);
}

