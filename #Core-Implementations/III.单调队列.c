#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int INIT_CAP = 6;

typedef struct ArrayDeque ArrayDeque;
typedef struct MonotonicQueue MonotonicQueue;

struct ArrayDeque {
	int* data;
	int size;
	int capacity;
	int front;
	int rear;
};

struct MonotonicQueue {
	ArrayDeque* dataQueue;
	ArrayDeque* maxQueue;
	ArrayDeque* minQueue;
};

MonotonicQueue* initMonotonicQueue();
void monotonicQueuePush(MonotonicQueue* queue, int value);
void monotonicQueuePop(MonotonicQueue* queue);
bool monotonicQueuePeek(MonotonicQueue* queue, int* result);
bool monotonicQueueGetMax(MonotonicQueue* queue, int* result);
bool monotonicQueueGetMin(MonotonicQueue* queue, int* result);
int monotonicQueueGetSize(MonotonicQueue* queue);
void monotonicQueueDelete(MonotonicQueue* queue);

int main(int argc, const char* argv[]) {
	MonotonicQueue* queue = initMonotonicQueue();
	int temp;

	printf("Number of elements: %d\n", monotonicQueueGetSize(queue));
	if (monotonicQueuePeek(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");
	//if (monotonicQueueGetMax(queue, &temp)) printf("Max: %d\n", temp);
	//else printf("No elements in queue.\n");
	//if (monotonicQueueGetMin(queue, &temp)) printf("Min: %d\n", temp);
	//else printf("No elements in queue.\n");

	monotonicQueuePush(queue, 10);
	monotonicQueuePush(queue, 20);
	monotonicQueuePush(queue, 30);
	monotonicQueuePush(queue, 40);
	monotonicQueuePush(queue, 50);
	monotonicQueuePop(queue);
	monotonicQueuePop(queue);
	printf("Number of elements: %d\n", monotonicQueueGetSize(queue));
	if (monotonicQueuePeek(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");
	if (monotonicQueueGetMax(queue, &temp)) printf("Max: %d\n", temp);
	else printf("No elements in queue.\n");
	if (monotonicQueueGetMin(queue, &temp)) printf("Min: %d\n", temp);
	else printf("No elements in queue.\n");

	monotonicQueuePush(queue, 60);
	monotonicQueuePush(queue, 70);
	monotonicQueuePush(queue, 80);
	monotonicQueuePush(queue, 90);
	monotonicQueuePop(queue);
	monotonicQueuePop(queue);
	monotonicQueuePop(queue);
	printf("Number of elements: %d\n", monotonicQueueGetSize(queue));
	if (monotonicQueuePeek(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");
	if (monotonicQueueGetMax(queue, &temp)) printf("Max: %d\n", temp);
	else printf("No elements in queue.\n");
	if (monotonicQueueGetMin(queue, &temp)) printf("Min: %d\n", temp);
	else printf("No elements in queue.\n");

	monotonicQueueDelete(queue);
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

MonotonicQueue* initMonotonicQueue() {
	MonotonicQueue* queue = (MonotonicQueue*)malloc(sizeof(MonotonicQueue));
	if (!queue) exit(EXIT_FAILURE);
	queue->dataQueue = initArrayDeque();
	queue->maxQueue = initArrayDeque();
	queue->minQueue = initArrayDeque();
	return queue;
}

void monotonicQueuePush(MonotonicQueue* queue, int value) {
	int temp;
	while (arrayDequePeekRear(queue->maxQueue, &temp) && temp < value) {
		arrayDequePopRear(queue->maxQueue);
	}
	arrayDequePushRear(queue->maxQueue, value);

	while (arrayDequePeekRear(queue->minQueue, &temp) && temp > value) {
		arrayDequePopRear(queue->minQueue);
	}
	arrayDequePushRear(queue->minQueue, value);

	arrayDequePushRear(queue->dataQueue, value);
}

void monotonicQueuePop(MonotonicQueue* queue) {
	if (queue->dataQueue->size > 0) {
		int temp1, temp2;
		arrayDequePeekFront(queue->dataQueue, &temp1);

		arrayDequePeekFront(queue->maxQueue, &temp2);
		if (temp1 == temp2) arrayDequePopFront(queue->maxQueue);
		arrayDequePeekFront(queue->minQueue, &temp2);
		if (temp1 == temp2) arrayDequePopFront(queue->minQueue);

		arrayDequePopFront(queue->dataQueue);
	}
}

bool monotonicQueuePeek(MonotonicQueue* queue, int* result) {
	return arrayDequePeekFront(queue->dataQueue, result);
}

bool monotonicQueueGetMax(MonotonicQueue* queue, int* result) {
	return arrayDequePeekFront(queue->maxQueue, result);
}

bool monotonicQueueGetMin(MonotonicQueue* queue, int* result) {
	return arrayDequePeekFront(queue->minQueue, result);
}

int monotonicQueueGetSize(MonotonicQueue* queue) {
	return queue->dataQueue->size;
}

void monotonicQueueDelete(MonotonicQueue* queue) {
	arrayDequeDelete(queue->dataQueue);
	arrayDequeDelete(queue->maxQueue);
	arrayDequeDelete(queue->minQueue);
	free(queue);
}