#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct HashNode HashNode;
typedef struct HashMap HashMap;

struct HashNode {
    int key;
    int value;
    HashNode* next;
};

struct HashMap {
	HashNode** buckets;
	int size;
	int capacity;
};

const int INIT_CAPACITY = 6;

int hashFunction(int capacity, int key);
HashNode* initHashMap(int initCapacity);
bool hashMapGet(HashMap* map, int key, int* result);
void hashMapPut(HashMap* map, int key, int value);
void hashMapRemove(HashMap* map, int key);
void hashMapResize(HashMap* map, int newCapacity);
void hashMapTraversal(HashMap* map);
void hashMapDelete(HashMap* map);

int main(int argc, const char* argv[]) {
	HashMap* map = initHashMap(INIT_CAPACITY);
	hashMapPut(map, 0, 10);
	hashMapPut(map, 25, 20);
	hashMapPut(map, 50, 30);
	hashMapPut(map, 75, 40);
	hashMapPut(map, 13, 50);
	hashMapPut(map, 26, 60);
	hashMapPut(map, 39, 70);
	hashMapPut(map, 52, 80);
	hashMapTraversal(map);
	hashMapRemove(map, 25);
	hashMapRemove(map, 50);
	hashMapRemove(map, 13);
	hashMapRemove(map, 39);
	hashMapTraversal(map);

	int temp;
	if (hashMapGet(map, 75, &temp)) printf("Key 75: %d\n", temp);
	else printf("Key 75 not found.\n");
	if (hashMapGet(map, 25, &temp)) printf("Key 25: %d\n", temp);
	else printf("Key 25 not found.\n");
	hashMapDelete(map);
}

int hashFunction(int capacity, int key) {
	return (key & 0x7FFFFFFF) % capacity;
}

HashNode* initHashMap(int initCapacity) {
	HashMap* map = (HashMap*)malloc(sizeof(HashMap));
	if (!map) exit(EXIT_FAILURE);
	map->size = 0;
	if (initCapacity <= 0) map->capacity = 1;
	else map->capacity = initCapacity;
	map->buckets = (HashNode**)calloc(map->capacity, sizeof(HashNode*));
	if (!map->buckets) exit(EXIT_FAILURE);
	return map;
}

bool hashMapGet(HashMap* map, int key, int* result) {
	int index = hashFunction(map->capacity, key);
	HashNode* current = map->buckets[index];
	while (current != NULL) {
		if (current->key == key) {
			*result = current->value;
			return true;
		}
		current = current->next;
	}
	return false; // Key not found
}

void hashMapPut(HashMap* map, int key, int value) {
	int index = hashFunction(map->capacity, key);
	HashNode* current = map->buckets[index];
	while (current != NULL) {
		if (current->key == key) {
			current->value = value;
			return;
		}
		current = current->next;
	}
	HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
	if (!newNode) exit(EXIT_FAILURE);
	newNode->key = key;
	newNode->value = value;
	newNode->next = map->buckets[index];
	map->buckets[index] = newNode;
	map->size++;

	if (map->size > map->capacity * 0.75) {
		hashMapResize(map, map->capacity * 2);
	}
}

void hashMapRemove(HashMap* map, int key) {
	int index = hashFunction(map->capacity, key);
	HashNode* current = map->buckets[index];
	HashNode* prev = NULL;
	while (current != NULL) {
		if (current->key == key) {
			if (prev == NULL) map->buckets[index] = current->next;
			else prev->next = current->next;
			free(current);
			map->size--;
			if (map->capacity > INIT_CAPACITY && map->size < map->capacity * 0.125) {
				hashMapResize(map, map->capacity / 2);
			}
			return;
		}
		prev = current;
		current = current->next;
	}
}

void hashMapResize(HashMap* map, int newCapacity) {
	if (newCapacity <= 0) newCapacity = 1;
	HashNode** newBuckets = (HashNode**)calloc(newCapacity, sizeof(HashNode*));
	if (!newBuckets) exit(EXIT_FAILURE);

	for (int i = 0; i < map->capacity; i++) {
		HashNode* current = map->buckets[i];
		while (current != NULL) {
			HashNode* next = current->next;
			int newIndex = hashFunction(newCapacity, current->key);
			current->next = newBuckets[newIndex];
			newBuckets[newIndex] = current;
			current = next;
		}
	}

	free(map->buckets);
	map->buckets = newBuckets;
	map->capacity = newCapacity;
}

void hashMapTraversal(HashMap* map) {
	for (int i = 0; i < map->capacity; i++) {
		HashNode* current = map->buckets[i];
		while (current != NULL) {
			printf("%d\t", current->value);
			current = current->next;
		}
	}
	printf("\n");
}

void hashMapDelete(HashMap* map) {
	for (int i = 0; i < map->capacity; i++) {
		HashNode* current = map->buckets[i];
		while (current != NULL) {
			HashNode* next = current->next;
			free(current);
			current = next;
		}
	}
	free(map->buckets);
	free(map);
}