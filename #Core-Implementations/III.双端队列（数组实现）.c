#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int INIT_CAP = 6;

typedef struct ArrayDeque ArrayDeque;

struct ArrayDeque {
	int* data;
	int size;
	int capacity;
	int front;
	int rear;
};

ArrayDeque* initArrayDeque();
void arrayDequePushFront(ArrayDeque* queue, int value);
void arrayDequePushRear(ArrayDeque* queue, int value);
void arrayDequePopFront(ArrayDeque* queue);
void arrayDequePopRear(ArrayDeque* queue);
bool arrayDequePeekFront(ArrayDeque* queue, int* result);
bool arrayDequePeekRear(ArrayDeque* queue, int* result);
int arrayDequeGetSize(ArrayDeque* queue);
void arrayDequeDelete(ArrayDeque* queue);

int main(int argc, const char* argv[]) {
	ArrayDeque* queue = initArrayDeque();
	int temp;

	printf("Number of elements: %d\n", arrayDequeGetSize(queue));
	if (arrayDequePeekFront(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");

	arrayDequePushFront(queue, 10);
	arrayDequePushFront(queue, 20);
	arrayDequePushFront(queue, 30);
	arrayDequePushFront(queue, 40);
	arrayDequePushFront(queue, 50);
	arrayDequePopRear(queue);
	arrayDequePopRear(queue);
	printf("Number of elements: %d\n", arrayDequeGetSize(queue));
	if (arrayDequePeekFront(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");
	if (arrayDequePeekRear(queue, &temp)) printf("Rear: %d\n", temp);
	else printf("No elements in queue.\n");

	arrayDequePushRear(queue, 60);
	arrayDequePushRear(queue, 70);
	arrayDequePushRear(queue, 80);
	arrayDequePushRear(queue, 90);
	arrayDequePopFront(queue);
	arrayDequePopFront(queue);
	arrayDequePopFront(queue);
	printf("Number of elements: %d\n", arrayDequeGetSize(queue));
	if (arrayDequePeekFront(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");
	if (arrayDequePeekRear(queue, &temp)) printf("Rear: %d\n", temp);
	else printf("No elements in queue.\n");

	arrayDequeDelete(queue);
}

ArrayDeque* initArrayDeque() {
	ArrayDeque* queue = (ArrayDeque*)malloc(sizeof(ArrayDeque));
	if (!queue) exit(EXIT_FAILURE);
	queue->data = (int*)malloc(sizeof(int) * INIT_CAP);
	if (!queue->data) exit(EXIT_FAILURE);
	queue->size = 0;
	queue->capacity = INIT_CAP;
	queue->front = 0;
	queue->rear = 0;
	return queue;
}

void arrayDequeResize(ArrayDeque* queue, int newCapacity) {
	if (newCapacity <= 0) newCapacity = 1;
	int* newDataArray = (int*)malloc(sizeof(int) * newCapacity);
	if (!newDataArray) exit(EXIT_FAILURE);


	for (int i = 0; i < queue->size; i++) {
		newDataArray[i] = queue->data[(queue->front + i) % queue->capacity];
	}

	free(queue->data);
	queue->data = newDataArray;
	queue->capacity = newCapacity;
	queue->front = 0;
	queue->rear = queue->size;
}

void arrayDequePushFront(ArrayDeque* queue, int value) {
	if (queue->size >= queue->capacity) {
		arrayDequeResize(queue, queue->capacity * 2);
	}

	queue->front = (queue->front - 1 + queue->capacity) % queue->capacity;
	queue->data[queue->front] = value;
	queue->size++;
}

void arrayDequePushRear(ArrayDeque* queue, int value) {
	if (queue->size >= queue->capacity) {
		arrayDequeResize(queue, queue->capacity * 2);
	}

	queue->data[queue->rear] = value;
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->size++;
}

void arrayDequePopFront(ArrayDeque* queue) {
	if (queue->size > 0) {
		queue->front = (queue->front + 1) % queue->capacity;
		queue->size--;
	}
	else return;

	if (queue->size > INIT_CAP && queue->size < queue->capacity / 2) {
		arrayDequeResize(queue, queue->capacity / 2);
	}
}

void arrayDequePopRear(ArrayDeque* queue) {
	if (queue->size > 0) {
		queue->rear = (queue->rear - 1 + queue->capacity) % queue->capacity;
		queue->size--;
	}
	else return;

	if (queue->size > INIT_CAP && queue->size < queue->capacity / 2) {
		arrayDequeResize(queue, queue->capacity / 2);
	}
}

bool arrayDequePeekFront(ArrayDeque* queue, int* result) {
	if (queue->size > 0) {
		*result = queue->data[queue->front];
		return true;
	}
	return false;
}

bool arrayDequePeekRear(ArrayDeque* queue, int* result) {
	if (queue->size > 0) {
		*result = queue->data[(queue->rear - 1 + queue->capacity) % queue->capacity];
		return true;
	}
	return false;
}

int arrayDequeGetSize(ArrayDeque* queue) {
	return queue->size;
}

void arrayDequeDelete(ArrayDeque* queue) {
	free(queue->data);
	free(queue);
}