#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node Node;
typedef struct LinkedDeque LinkedDeque;

struct Node {
	int value;
	Node* prev;
	Node* next;
};

struct LinkedDeque {
	Node* front;
	Node* rear;
	int size;
};

LinkedDeque* initLinkedDeque();
void linkedDequePushFront(LinkedDeque* queue, int value);
void linkedDequePushRear(LinkedDeque* queue, int value);
void linkedDequePopFront(LinkedDeque* queue);
void linkedDequePopRear(LinkedDeque* queue);
bool linkedDequePeekFront(LinkedDeque* queue, int* result);
bool linkedDequePeekRear(LinkedDeque* queue, int* result);
int linkedDequeGetSize(LinkedDeque* queue);
void linkedDequeDelete(LinkedDeque* queue);

int main(int argc, const char* argv[]) {
	LinkedDeque* queue = initLinkedDeque();
	int temp;

	printf("Number of elements: %d\n", linkedDequeGetSize(queue));
	if (linkedDequePeekFront(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");

	linkedDequePushFront(queue, 10);
	linkedDequePushFront(queue, 20);
	linkedDequePushFront(queue, 30);
	linkedDequePushFront(queue, 40);
	linkedDequePushFront(queue, 50);
	linkedDequePopRear(queue);
	linkedDequePopRear(queue);
	printf("Number of elements: %d\n", linkedDequeGetSize(queue));
	if (linkedDequePeekFront(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");
	if (linkedDequePeekRear(queue, &temp)) printf("Rear: %d\n", temp);
	else printf("No elements in queue.\n");

	linkedDequePushRear(queue, 60);
	linkedDequePushRear(queue, 70);
	linkedDequePushRear(queue, 80);
	linkedDequePushRear(queue, 90);
	linkedDequePopFront(queue);
	linkedDequePopFront(queue);
	linkedDequePopFront(queue);
	printf("Number of elements: %d\n", linkedDequeGetSize(queue));
	if (linkedDequePeekFront(queue, &temp)) printf("Front: %d\n", temp);
	else printf("No elements in queue.\n");
	if (linkedDequePeekRear(queue, &temp)) printf("Rear: %d\n", temp);
	else printf("No elements in queue.\n");

	linkedDequeDelete(queue);
}

LinkedDeque* initLinkedDeque() {
	LinkedDeque* queue = (LinkedDeque*)malloc(sizeof(LinkedDeque));
	if (!queue) exit(EXIT_FAILURE);
	queue->front = (Node*)malloc(sizeof(Node));
	if (!queue->front) exit(EXIT_FAILURE);
	queue->rear = (Node*)malloc(sizeof(Node));
	if (!queue->rear) exit(EXIT_FAILURE);
	queue->front->next = queue->rear;
	queue->rear->prev = queue->front;
	queue->size = 0;
	return queue;
}

void linkedDequePushFront(LinkedDeque* queue, int value) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	if (!newnode) exit(EXIT_FAILURE);
	newnode->value = value;
	newnode->next = queue->front->next;
	newnode->prev = queue->front;
	queue->front->next->prev = newnode;
	queue->front->next = newnode;
	queue->size++;
}

void linkedDequePushRear(LinkedDeque* queue, int value) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	if (!newnode) exit(EXIT_FAILURE);
	newnode->value = value;
	newnode->next = queue->rear;
	newnode->prev = queue->rear->prev;
	queue->rear->prev->next = newnode;
	queue->rear->prev = newnode;
	queue->size++;
}

void linkedDequePopFront(LinkedDeque* queue) {
	if (queue->size > 0) {
		Node* temp = queue->front->next;
		queue->front->next = temp->next;
		temp->next->prev = queue->front;
		free(temp);
		queue->size--;
	}
}

void linkedDequePopRear(LinkedDeque* queue) {
	if (queue->size > 0) {
		Node* temp = queue->rear->prev;
		queue->rear->prev = temp->prev;
		temp->prev->next = queue->rear;
		free(temp);
		queue->size--;
	}
}

bool linkedDequePeekFront(LinkedDeque* queue, int* result) {
	if (queue->size > 0) {
		*result = queue->front->next->value;
		return true;
	}
	return false;
}

bool linkedDequePeekRear(LinkedDeque* queue, int* result) {
	if (queue->size > 0) {
		*result = queue->rear->prev->value;
		return true;
	}
	return false;
}

int linkedDequeGetSize(LinkedDeque* queue) {
	return queue->size;
}

void linkedDequeDelete(LinkedDeque* queue) {
	Node* p = queue->front->next;
	while (p != queue->rear) {
		Node* next = p->next;
		free(p);
		p = next;
	}
	free(queue->front);
	free(queue->rear);
	free(queue);
}