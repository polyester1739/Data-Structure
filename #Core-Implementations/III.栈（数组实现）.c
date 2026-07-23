#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int INIT_CAPACITY = 6;

typedef struct ArrayStack ArrayStack;

struct ArrayStack {
	int* data;
	int size;
	int capacity;
};

ArrayStack* initArrayStack();
void arrayStackPush(ArrayStack* stack, int value);
void arrayStackPop(ArrayStack* stack);
bool arrayStackPeek(ArrayStack* stack, int* result);
int arrayStackGetSize(ArrayStack* stack);
void arrayStackDelete(ArrayStack* stack);

int main(int argc, const char* argv[]) {
	ArrayStack* stack = initArrayStack();
	int temp;

	printf("Number of elements: %d\n", arrayStackGetSize(stack));
	if (arrayStackPeek(stack, &temp)) printf("Top: %d\n", temp);
	else printf("No elements in stack.\n");

	arrayStackPush(stack, 10);
	arrayStackPush(stack, 20);
	arrayStackPush(stack, 30);
	arrayStackPush(stack, 40);
	arrayStackPush(stack, 50);
	arrayStackPop(stack);
	arrayStackPop(stack);
	printf("Number of elements: %d\n", arrayStackGetSize(stack));
	if (arrayStackPeek(stack, &temp)) printf("Top: %d\n", temp);
	else printf("No elements in stack.\n");

	arrayStackPush(stack, 60);
	arrayStackPush(stack, 70);
	printf("Number of elements: %d\n", arrayStackGetSize(stack));
	if (arrayStackPeek(stack, &temp)) printf("Top: %d\n", temp);
	else printf("No elements in stack.\n");

	arrayStackDelete(stack);
}

ArrayStack* initArrayStack() {
	ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
	if (!stack) exit(EXIT_FAILURE);
	stack->data = (int*)malloc(sizeof(int) * INIT_CAPACITY);
	if (!stack->data) exit(EXIT_FAILURE);
	stack->size = 0;
	stack->capacity = INIT_CAPACITY;
	return stack;
}

void arrayStackResize(ArrayStack* stack, int newCapacity) {
	if (newCapacity <= 0) newCapacity = 1;
	int* newDataArray = (int*)malloc(sizeof(int) * newCapacity);
	if (!newDataArray) exit(EXIT_FAILURE);

	for (int i = 0; i < stack->size; i++) newDataArray[i] = stack->data[i];
	free(stack->data);
	stack->data = newDataArray;
	stack->capacity = newCapacity;
}

void arrayStackPush(ArrayStack* stack, int value) {
	if (stack->size >= stack->capacity) {
		arrayStackResize(stack, stack->capacity * 2);
	}

	stack->data[stack->size] = value;
	stack->size++;
}

void arrayStackPop(ArrayStack* stack) {
	if (stack->size > 0) stack->size--;
	else return;

	if (stack->size > INIT_CAPACITY && stack->size < stack->capacity / 2) {
		arrayStackResize(stack, stack->capacity / 2);
	}
}

bool arrayStackPeek(ArrayStack* stack, int* result) {
	if (stack->size > 0) {
		*result = stack->data[stack->size - 1];
		return true;
	}
	return false;
}

int arrayStackGetSize(ArrayStack* stack) {
	return stack->size;
}

void arrayStackDelete(ArrayStack* stack) {
	free(stack->data);
	free(stack);
}