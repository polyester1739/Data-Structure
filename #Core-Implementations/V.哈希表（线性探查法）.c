#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int INIT_CAPACITY = 6;

typedef struct KVNode KVNode;
typedef struct HashMap HashMap;

struct KVNode {
	int key;
	int value;
};

struct HashMap {
	KVNode** table;
	int size;
	int capacity;
};

int hashFunction(int key, int capacity);
HashMap* initHashMap();
int findIndex(HashMap* map, int key);
bool hashMapGet(HashMap* map, int key, int* value);
void hashMapPut(HashMap* map, int key, int value);
void hashMapRemove(HashMap* map, int key);
void hashMapResize(HashMap* map, int newCapacity);
void hashMapTraversal(HashMap* map);
void hashMapDelete(HashMap* map);

int main(int argc, const char* argv[]) {
	HashMap* map = initHashMap();
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

int hashFunction(int key, int capacity) {
	return (key & 0x7FFFFFFF) % capacity;
}

HashMap* initHashMap() {
	HashMap* map = (HashMap*)malloc(sizeof(HashMap));
	if (!map) exit(EXIT_FAILURE);
	map->table = (KVNode**)calloc(INIT_CAPACITY, sizeof(KVNode*));
	if (!map->table) exit(EXIT_FAILURE);
	map->size = 0;
	map->capacity = INIT_CAPACITY;
	return map;
}

int findIndex(HashMap* map, int key) {
	int index = hashFunction(key, map->capacity);
	while (map->table[index] != NULL) {
		if (map->table[index]->key == key) return index;
		index = (index + 1) % map->capacity;
	}
	return index;
}

bool hashMapGet(HashMap* map, int key, int* value) {
	int index = findIndex(map, key);
	if (map->table[index] != NULL) {
		*value = map->table[index]->value;
		return true;
	}
	return false;	// Key not found
}

void hashMapPut(HashMap* map, int key, int value) {
	int index = findIndex(map, key);

	if (map->table[index] != NULL) {
		map->table[index]->value = value;
		return;
	}

	KVNode* newnode = (KVNode*)malloc(sizeof(KVNode));
	if (!newnode) exit(EXIT_FAILURE);
	newnode->key = key;
	newnode->value = value;
	map->table[index] = newnode;
	map->size++;

	if (map->size > map->capacity * 0.75) {
		hashMapResize(map, map->capacity * 2);
	}
}

void hashMapRemove(HashMap* map, int key) {
	int index = findIndex(map, key);
	if (map->table[index] != NULL) {
		free(map->table[index]);
		map->table[index] = NULL;
		map->size--;

		index = (index + 1) % map->capacity;
		for (; map->table[index] != NULL; index = (index + 1) % map->capacity) {
			KVNode* temp = map->table[index];
			map->table[index] = NULL;
			map->size--;
			hashMapPut(map, temp->key, temp->value);
			free(temp);
		}

		if (map->size > INIT_CAPACITY && map->size < map->capacity * 0.125) {
			hashMapResize(map, map->capacity / 2);
		}
	}
}

void hashMapResize(HashMap* map, int newCapacity) {
	if (newCapacity <= 0) newCapacity = 1;
	KVNode** newTable = (KVNode**)calloc(newCapacity, sizeof(KVNode*));
	if (!newTable) exit(EXIT_FAILURE);

	for (int i = 0; i < map->capacity; i++) {
		if (map->table[i] != NULL) {
			int index = hashFunction(map->table[i]->key, newCapacity);
			while (newTable[index] != NULL) index = (index + 1) % newCapacity;
			newTable[index] = map->table[i];
		}
	}

	free(map->table);
	map->table = newTable;
	map->capacity = newCapacity;
}

void hashMapTraversal(HashMap* map) {
	for (int i = 0; i < map->capacity; i++) {
		if (map->table[i] != NULL) printf("%d\t", map->table[i]->value);
	}
	printf("\n");
}

void hashMapDelete(HashMap* map) {
	for (int i = 0; i < map->capacity; i++) {
		if (map->table[i] != NULL) free(map->table[i]);
	}
	free(map->table);
	free(map);
}