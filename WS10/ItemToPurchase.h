/**
 * Description: Create ItemToPurchase struct
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 04/09/2023
 * Creation date: 04/08/2023
 **/


#ifndef ITEMTOPURCHASE_H
#define ITEMTOPURCHASE_H
#define MAX_LENGTH 100

typedef struct ItemToPurchase {
    char    itemName[MAX_LENGTH];
    int     itemPrice;
    int     itemQuantity;
} ItemToPurchase;

void MakeItemBlank(ItemToPurchase *resetItem);
void PrintItemCost(ItemToPurchase printItem);

#endif 

