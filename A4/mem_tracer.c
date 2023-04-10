/**
 * Description: This program
 * Author names: Kimlong Hor, Jimmy Phan
 * Author emails: kimlong.hor@sjsu.edu, jimmy.phan@sjsu.edu
 * Last modified date: 04/10/2023
 * Creation date: 04/08/2023
 **/
 
 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

// Define LinkedList and its node structs
typedef struct Node {
    	char* data;
    	int index;
    	struct Node* next;
} Node;

typedef struct LinkedList {
	Node *head;
} LinkedList;

LinkedList* initLinkedList() {
	LinkedList* list = malloc(sizeof(LinkedList));
	list->head = malloc(sizeof(Node));
	return list;
}

Node* createNewNode(char* data, int index) {
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->index = index;
	return node;
}

void PrintNodes(Node *head) {
	if (head == NULL) {
		printf("\n");
		return;
	}
	printf("Node #%d -> %s", head->index, head->data);
	PrintNodes(head->next);
}

char** initArray(int size) {
	char** a = malloc(size * sizeof(char*));
	return a;
}

int main(void) {
	
	char* input = NULL;
	size_t inputLength = 0;
 	unsigned char inputCount = 0;
	
	int allocatedSize = 10;
	char** inputArray = initArray(allocatedSize);
	
	LinkedList *list = initLinkedList();
	Node *currentNode = list->head;
	
	while (getline(&input, &inputLength, stdin) != -1) {
		inputArray[inputCount] = strdup(input);
		if (inputCount == 0) {
			list->head->data = inputArray[inputCount];
			list->head->index = inputCount + 1;
		} else {
			currentNode->next = createNewNode(inputArray[inputCount], inputCount + 1);
			currentNode = currentNode->next;
		}
 		inputCount++;
 	}
 	
 	PrintNodes(list->head);
	
	return 0;
}
