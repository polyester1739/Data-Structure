#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int INIT_CAP = 6;

typedef struct ArrayQueue ArrayQueue;

struct ArrayQueue {
	int* data;
	int size;
	int capacity;
	int front;
	int rear;
};

ArrayQueue* initArrayQueue();
void arrayQueuePush(ArrayQueue* queue, int value);
void arrayQueuePop(ArrayQueue* queue);
bool arrayQueuePeek(ArrayQueue* queue, int* result);
int arrayQueueGetSize(ArrayQueue* queue);
void arrayQueueDelete(ArrayQueue* queue);

int main(int argc, const char* argv[]) {
	ArrayQueue* queue = initArrayQueue();
	int temp;

	printf("Number of elements: %d\n", arrayQueueGetSize(queue));
	if (arrayQueuePeek(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");

	arrayQueuePush(queue, 10);
	arrayQueuePush(queue, 20);
	arrayQueuePush(queue, 30);
	arrayQueuePush(queue, 40);
	arrayQueuePush(queue, 50);
	arrayQueuePop(queue);
	arrayQueuePop(queue);
	printf("Number of elements: %d\n", arrayQueueGetSize(queue));
	if (arrayQueuePeek(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");

	arrayQueuePush(queue, 60);
	arrayQueuePush(queue, 70);
	printf("Number of elements: %d\n", arrayQueueGetSize(queue));
	if (arrayQueuePeek(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");

	arrayQueueDelete(queue);
}

ArrayQueue* initArrayQueue() {
	ArrayQueue* queue = (ArrayQueue*)malloc(sizeof(ArrayQueue));
	if (!queue) exit(EXIT_FAILURE);
	queue->data = (int*)malloc(sizeof(int) * INIT_CAP);
	if (!queue->data) exit(EXIT_FAILURE);
	queue->size = 0;
	queue->capacity = INIT_CAP;
	queue->front = 0;
	queue->rear = 0;
	return queue;
}

void arrayQueueResize(ArrayQueue* queue, int newCapacity) {
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

void arrayQueuePush(ArrayQueue* queue, int value) {
	if (queue->size >= queue->capacity) {
		arrayQueueResize(queue, queue->capacity * 2);
	}

	queue->data[queue->rear] = value;
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->size++;
}

void arrayQueuePop(ArrayQueue* queue) {
	if (queue->size > 0) {
		queue->front = (queue->front + 1) % queue->capacity;
		queue->size--;
	}
	else return;

	if (queue->size > INIT_CAP && queue->size < queue->capacity / 2) {
		arrayQueueResize(queue, queue->capacity / 2);
	}
}

bool arrayQueuePeek(ArrayQueue* queue, int* result) {
	if (queue->size > 0) {
		*result = queue->data[queue->front];
		return true;
	}
	return false;
}

int arrayQueueGetSize(ArrayQueue* queue) {
	return queue->size;
}

void arrayQueueDelete(ArrayQueue* queue) {
	free(queue->data);
	free(queue);
}