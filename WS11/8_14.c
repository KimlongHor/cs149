/**
 * Description: This program takes three names and phone numbers as inputs and build a linked list with 3 nodes using them. 
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 04/17/2023
 * Creation date: 04/16/2023
 **/
 
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 // Define ContactNode struct
 typedef struct ContactNode_struct {
 	char* contactName;
 	char* contactPhoneNumber;
 	struct ContactNode_struct* nextNodePtr;
 } ContactNode;

/*
 This function creates and initializes a contactNode 
 Assumption: None
 Inputs: two char pointers
 Return: ContactNode pointer
 */
ContactNode* InitializeContactNode(char* name, char* phoneNumber) {
	ContactNode* node = malloc(sizeof(ContactNode));
	node->contactName = malloc(strlen(name) * sizeof(char));
	node->contactPhoneNumber = malloc(strlen(phoneNumber) * sizeof(char));
	node->nextNodePtr = NULL;
	
	strcpy(node->contactName, name);
	strcpy(node->contactPhoneNumber, phoneNumber);
	return node;
}

/*
 This function returns contactName from the node
 Assumption: None
 Inputs: a contactNode pointer
 Return: a char pointer
 */
char* GetName(ContactNode* node) {
	return node->contactName;
}

/*
 This function returns contact phone number from the node
 Assumption: None
 Inputs: a contactNode pointer
 Return: a char pointer
 */
char* GetPhoneNumber(ContactNode* node) {
	return node->contactPhoneNumber;
}

/*
 This function inserts a new node after a node
 Assumption: None
 Inputs: a pointer of current node and a pointer of the new node
 Return: Void
 */
void InsertAfter(ContactNode* curNode, ContactNode* nextNode) {
	curNode->nextNodePtr = nextNode;
}

/*
 This function return the next node
 Assumption: None
 Inputs: a contactNode pointer
 Return: a contactNode pointer
 */
ContactNode* GetNext(ContactNode* curNode) {
	return curNode->nextNodePtr;
}

/*
 This function prints the content of a node
 Assumption: None
 Inputs: a contactNode pointer
 Return: Void
 */
void PrintContactNode(ContactNode* node) {
	printf("Name: %s\nPhone number: %s\n\n", node->contactName, node->contactPhoneNumber);
}

/*
 This function frees the linked list from the memory
 Assumption: None
 Inputs: a contactNode pointer
 Return: Void
 */
void freeLinkedList(ContactNode* head) {
	ContactNode* current = head;
	ContactNode* next = NULL;
	
	while(current != NULL) {
		next = current->nextNodePtr;
		free(current->contactName);
		free(current->contactPhoneNumber);
		free(current);
		current = next;
	}
}
 
 int main(void) {
 	char* nameInput = NULL;
	size_t nameInputLength = 0;
	
	char* phoneNumInput = NULL;
	size_t phoneNumInputLength = 0;
	
	ContactNode* head = NULL;
	ContactNode* curNode = NULL;
	
	int counter = 3;
	
	printf("Please enter 3 names and phone numbers.\n");	
	while(counter > 0) {
		printf("Enter a name: ");
		getline(&nameInput, &nameInputLength, stdin);
		printf("Enter a phone number: ");
		getline(&phoneNumInput, &phoneNumInputLength, stdin);
		
		// replace the "\n" with "\0"
		nameInput[strcspn(nameInput, "\n")] = '\0';
		phoneNumInput[strcspn(phoneNumInput, "\n")] = '\0';
		
		if (head == NULL) {
			head = InitializeContactNode(nameInput, phoneNumInput);
			curNode = head;
		} else {
			ContactNode* newNode = InitializeContactNode(nameInput, phoneNumInput);
			InsertAfter(curNode, newNode);
			curNode = newNode;
		}
		
		counter--;
	}
 	
 	// print the content in the linkedlist
 	printf("CONTACT LIST\n");
 	ContactNode* temp = head;
 	while(temp != NULL) {
 		PrintContactNode(temp);
 		temp = temp->nextNodePtr;
 	}
 	
 	freeLinkedList(head);
 	free(nameInput);
 	free(phoneNumInput);
 	
 	return 0;
 }
