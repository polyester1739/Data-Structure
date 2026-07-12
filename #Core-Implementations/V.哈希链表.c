#include <stdio.h>
#include <stdlib.h>

const int INIT_CAPACITY = 6;

typedef struct Node Node;
typedef struct LinkedHashMap LinkedHashMap;

struct Node {
	int key;
	int value;
	Node* hashNext;
	Node* prev;
	Node* next;
};

struct LinkedHashMap {
	Node** hashMap;
	int size;
	int capacity;
	Node* head;
	Node* tail;
};

int hashFunction(int capacity, int key);
LinkedHashMap* initLinkedHashMap();
int linkedHashMapGet(LinkedHashMap* map, int key);
void linkedHashMapPut(LinkedHashMap* map, int key, int value);
void linkedHashMapRemove(LinkedHashMap* map, int key);
void linkedHashMapResize(LinkedHashMap* map, int newCapacity);
void linkedHashMapTraverseInOrder(LinkedHashMap* map);
void linkedHashMapTraverseWithoutOrder(LinkedHashMap* map);
void linkedHashMapDelete(LinkedHashMap* map);

int main(int argc, const char* argv[]) {
	LinkedHashMap* map = initLinkedHashMap();
	linkedHashMapPut(map, 0, 10);
	linkedHashMapPut(map, 25, 20);
	linkedHashMapPut(map, 50, 30);
	linkedHashMapPut(map, 75, 40);
	linkedHashMapPut(map, 13, 50);
	linkedHashMapPut(map, 26, 60);
	linkedHashMapPut(map, 39, 70);
	linkedHashMapPut(map, 52, 80);
	linkedHashMapTraverseInOrder(map);
	linkedHashMapTraverseWithoutOrder(map);
	linkedHashMapRemove(map, 25);
	linkedHashMapRemove(map, 50);
	linkedHashMapRemove(map, 13);
	linkedHashMapRemove(map, 39);
	linkedHashMapTraverseInOrder(map);
	linkedHashMapTraverseWithoutOrder(map);
	printf("Key 75: %d\n", linkedHashMapGet(map, 75));
	printf("Key 25: %d\n", linkedHashMapGet(map, 25));
	linkedHashMapDelete(map);
}

int hashFunction(int capacity, int key) {
	return (key & 0x7FFFFFFF) % capacity;
}

LinkedHashMap* initLinkedHashMap() {
	LinkedHashMap* map = (LinkedHashMap*)malloc(sizeof(LinkedHashMap));
	if (!map) exit(EXIT_FAILURE);
	map->hashMap = (Node**)calloc(INIT_CAPACITY, sizeof(Node*));
	map->size = 0;
	map->capacity = INIT_CAPACITY;
	map->head = (Node*)malloc(sizeof(Node));
	map->tail = (Node*)malloc(sizeof(Node));
	map->head->next = map->tail;
	map->tail->prev = map->head;
	return map;
}

int linkedHashMapGet(LinkedHashMap* map, int key) {
	int index = hashFunction(map->capacity, key);
	Node* cur = map->hashMap[index];
	while (cur != NULL) {
		if (cur->key == key) return cur->value;
		cur = cur->hashNext;
	}
	return -1; // Key not found
}

void linkedHashMapPut(LinkedHashMap* map, int key, int value) {
	int index = hashFunction(map->capacity, key);
	Node* cur = map->hashMap[index];
	while (cur != NULL) {
		if (cur->key == key) {
			cur->value = value;
			return;
		}
		cur = cur->hashNext;
	}
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->key = key;
	newnode->value = value;
	newnode->hashNext = map->hashMap[index];
	map->hashMap[index] = newnode;
	newnode->prev = map->tail->prev;
	newnode->next = map->tail;
	map->tail->prev->next = newnode;
	map->tail->prev = newnode;
	map->size++;

	if (map->size > map->capacity * 0.75) {
		linkedHashMapResize(map, map->capacity * 2);
	}
}

void linkedHashMapRemove(LinkedHashMap* map, int key) {
	int index = hashFunction(map->capacity, key);
	Node* cur = map->hashMap[index];
	Node* hashPrev = NULL;

	while (cur != NULL) {
		if (cur->key == key) {
			if (hashPrev == NULL) map->hashMap[index] = cur->hashNext;
			else hashPrev->hashNext = cur->hashNext;
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			free(cur);
			map->size--;
			if (map->size < map->capacity * 0.125 && map->capacity > INIT_CAPACITY) {
				linkedHashMapResize(map, map->capacity / 2);
			}
			return;
		}
		hashPrev = cur;
		cur = cur->hashNext;
	}
}

void linkedHashMapResize(LinkedHashMap* map, int newCapacity) {
	Node** newMap = (Node**)calloc(newCapacity, sizeof(Node*));
	if (!newMap) exit(EXIT_FAILURE);
	for (int i = 0; i < map->capacity; i++) {
		Node* cur = map->hashMap[i];
		while (cur != NULL) {
			int newIndex = hashFunction(newCapacity, cur->key);
			Node* nextNode = cur->hashNext;
			cur->hashNext = newMap[newIndex];
			newMap[newIndex] = cur;
			cur = nextNode;
		}
	}
	free(map->hashMap);
	map->hashMap = newMap;
	map->capacity = newCapacity;
}

void linkedHashMapTraverseInOrder(LinkedHashMap* map) {
	Node* p = map->head->next;
	while (p != map->tail) {
		printf("%d\t", p->value);
		p = p->next;
	}
	printf("\n");
}

void linkedHashMapTraverseWithoutOrder(LinkedHashMap* map) {
	for (int i = 0; i < map->capacity; i++) {
		Node* cur = map->hashMap[i];
		while (cur != NULL) {
			printf("%d\t", cur->value);
			cur = cur->hashNext;
		}
	}
	printf("\n");
}

void linkedHashMapDelete(LinkedHashMap* map) {
	Node* p = map->head->next;
	while (p != map->tail) {
		Node* nextNode = p->next;
		free(p);
		p = nextNode;
	}
	free(map->head);
	free(map->tail);
	free(map->hashMap);
	free(map);
}