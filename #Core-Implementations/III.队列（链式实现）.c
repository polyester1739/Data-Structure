#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node Node;
typedef struct LinkedQueue LinkedQueue;

struct Node {
	int value;
	Node* next;
};

struct LinkedQueue {
	Node* front;
	Node* rear;
	int size;
};

LinkedQueue* initLinkedQueue();
void linkedQueuePush(LinkedQueue* queue, int value);
void linkedQueuePop(LinkedQueue* queue);
bool linkedQueuePeek(LinkedQueue* queue, int* result);
int linkedQueueGetSize(LinkedQueue* queue);
void linkedQueueDelete(LinkedQueue* queue);

int main(int argc, const char* argv[]) {
	LinkedQueue* queue = initLinkedQueue();
	int temp;

	printf("Number of elements: %d\n", linkedQueueGetSize(queue));
	if (linkedQueuePeek(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");

	linkedQueuePush(queue, 10);
	linkedQueuePush(queue, 20);
	linkedQueuePush(queue, 30);
	linkedQueuePush(queue, 40);
	linkedQueuePush(queue, 50);
	linkedQueuePop(queue);
	linkedQueuePop(queue);
	printf("Number of elements: %d\n", linkedQueueGetSize(queue));
	if (linkedQueuePeek(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");

	linkedQueuePush(queue, 60);
	linkedQueuePush(queue, 70);
	printf("Number of elements: %d\n", linkedQueueGetSize(queue));
	if (linkedQueuePeek(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");

	linkedQueueDelete(queue);
}

LinkedQueue* initLinkedQueue() {
	LinkedQueue* queue = (LinkedQueue*)malloc(sizeof(LinkedQueue));
	if (!queue) exit(EXIT_FAILURE);
	queue->front = (Node*)malloc(sizeof(Node));
	if (!queue->front) exit(EXIT_FAILURE);
	queue->front->next = NULL;
	queue->rear = queue->front;
	queue->size = 0;
	return queue;
}

void linkedQueuePush(LinkedQueue* queue, int value) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	if (!newnode) exit(EXIT_FAILURE);
	newnode->value = value;
	newnode->next = NULL;
	queue->rear->next = newnode;
	queue->rear = newnode;
	queue->size++;
}

void linkedQueuePop(LinkedQueue* queue) {
	if (queue->size > 0) {
		Node* temp = queue->front->next;
		if (temp == queue->rear) queue->rear = queue->front;
		queue->front->next = temp->next;
		free(temp);
		queue->size--;
	}
}

bool linkedQueuePeek(LinkedQueue* queue, int* result) {
	if (queue->size > 0) {
		*result = queue->front->next->value;
		return true;
	}
	return false;
}

int linkedQueueGetSize(LinkedQueue* queue) {
	return queue->size;
}

void linkedQueueDelete(LinkedQueue* queue) {
	Node* p = queue->front;
	while (p != NULL) {
		Node* next = p->next;
		free(p);
		p = next;
	}
	free(queue);
}