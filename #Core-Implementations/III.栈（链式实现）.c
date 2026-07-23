#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node Node;
typedef struct LinkedStack LinkedStack;

struct Node {
	int value;
	Node* next;
};

struct LinkedStack {
	Node* head;
	int size;
};

LinkedStack* initLinkedStack();
void linkedStackPush(LinkedStack* stack, int value);
void linkedStackPop(LinkedStack* stack);
bool linkedStackPeek(LinkedStack* stack, int* result);
int linkedStackGetSize(LinkedStack* stack);
void linkedStackDelete(LinkedStack* stack);

int main(int argc, const char* argv[]) {
	LinkedStack* stack = initLinkedStack();
	int temp;

	printf("Number of elements: %d\n", linkedStackGetSize(stack));
	if (linkedStackPeek(stack, &temp)) printf("Top: %d\n", temp);
	else printf("No elements in stack.\n");

	linkedStackPush(stack, 10);
	linkedStackPush(stack, 20);
	linkedStackPush(stack, 30);
	linkedStackPush(stack, 40);
	linkedStackPush(stack, 50);
	linkedStackPop(stack);
	linkedStackPop(stack);
	printf("Number of elements: %d\n", linkedStackGetSize(stack));
	if (linkedStackPeek(stack, &temp)) printf("Top: %d\n", temp);
	else printf("No elements in stack.\n");

	linkedStackPush(stack, 60);
	linkedStackPush(stack, 70);
	printf("Number of elements: %d\n", linkedStackGetSize(stack));
	if (linkedStackPeek(stack, &temp)) printf("Top: %d\n", temp);
	else printf("No elements in stack.\n");

	linkedStackDelete(stack);
}

LinkedStack* initLinkedStack() {
	LinkedStack* stack = (LinkedStack*)malloc(sizeof(LinkedStack));
	if (!stack) exit(EXIT_FAILURE);
	stack->head = NULL;
	stack->size = 0;
	return stack;
}

void linkedStackPush(LinkedStack* stack, int value) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	if (!newnode) exit(EXIT_FAILURE);
	newnode->value = value;
	
	if (stack->head != NULL) {
		newnode->next = stack->head;
		stack->head = newnode;
	}
	else {
		newnode->next = NULL;
		stack->head = newnode;
	}
	stack->size++;
}

void linkedStackPop(LinkedStack* stack) {
	if (stack->size > 0) {
		Node* next = stack->head->next;
		free(stack->head);
		stack->head = next;
		stack->size--;
	}
}

bool linkedStackPeek(LinkedStack* stack, int* result) {
	if (stack->size > 0) {
		*result = stack->head->value;
		return true;
	}
	else return false;
}

int linkedStackGetSize(LinkedStack* stack) {
	return stack->size;
}

void linkedStackDelete(LinkedStack* stack) {
	Node* p = stack->head;
	while (p != NULL) {
		Node* next = p->next;
		free(p);
		p = next;
	}
	free(stack);
}