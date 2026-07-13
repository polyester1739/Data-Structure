#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct HashNode HashNode;
typedef struct HashTable HashTable;
typedef struct HashSet HashSet;

struct HashNode {
	int key;
	int value;
	HashNode* next;
};

struct HashTable {
	HashNode** buckets;
	int size;
	int capacity;
};

struct HashSet {
	HashTable* table;
};

const int INIT_CAPACITY = 6;

HashSet* initHashSet(int initCapacity);
void hashSetPut(HashSet* set, int key, int value);
void hashSetRemove(HashSet* set, int key);
bool hashSetContains(HashSet* set, int key);
int hashSetGetSize(HashSet* set);
void hashSetDelete(HashSet* set);

int main(int argc, const char* argv[]) {
	HashSet* set = initHashSet(INIT_CAPACITY);
	hashSetPut(set, 0, 10);
	hashSetPut(set, 25, 20);
	hashSetPut(set, 50, 30);
	hashSetPut(set, 75, 40);
	hashSetPut(set, 13, 50);
	hashSetPut(set, 26, 60);
	hashSetPut(set, 39, 70);
	hashSetPut(set, 52, 80);
	printf("Size: %d\n", hashSetGetSize(set));
	hashSetRemove(set, 25);
	hashSetRemove(set, 50);
	hashSetRemove(set, 13);
	hashSetRemove(set, 39);
	printf("Size: %d\n", hashSetGetSize(set));
	printf("Contains 75: %s\n", hashSetContains(set, 75) ? "true" : "false");
	printf("Contains 25: %s\n", hashSetContains(set, 25) ? "true" : "false");
	hashSetDelete(set);
}

int hashFunction(int capacity, int key) {
	return (key & 0x7FFFFFFF) % capacity;
}

void hashTableResize(HashTable* table, int newCapacity) {
	if (newCapacity <= 0) newCapacity = 1;
	HashNode** newBuckets = (HashNode**)calloc(newCapacity, sizeof(HashNode*));
	if (!newBuckets) exit(EXIT_FAILURE);

	for (int i = 0; i < table->capacity; i++) {
		HashNode* current = table->buckets[i];
		while (current != NULL) {
			HashNode* next = current->next;
			int newIndex = hashFunction(newCapacity, current->key);
			current->next = newBuckets[newIndex];
			newBuckets[newIndex] = current;
			current = next;
		}
	}

	free(table->buckets);
	table->buckets = newBuckets;
	table->capacity = newCapacity;
}

HashNode* initHashTable(int initCapacity) {
	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	if (!table) exit(EXIT_FAILURE);
	table->size = 0;
	if (initCapacity <= 0) table->capacity = 1;
	else table->capacity = initCapacity;
	table->buckets = (HashNode**)calloc(table->capacity, sizeof(HashNode*));
	if (!table->buckets) exit(EXIT_FAILURE);
	return table;
}

bool hashTableGet(HashTable* table, int key, int* result) {
	int index = hashFunction(table->capacity, key);
	HashNode* current = table->buckets[index];
	while (current != NULL) {
		if (current->key == key) {
			*result = current->value;
			return true;
		}
		current = current->next;
	}
	return false; // Key not found
}

void hashTablePut(HashTable* table, int key, int value) {
	int index = hashFunction(table->capacity, key);
	HashNode* current = table->buckets[index];
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
	newNode->next = table->buckets[index];
	table->buckets[index] = newNode;
	table->size++;

	if (table->size > table->capacity * 0.75) {
		hashTableResize(table, table->capacity * 2);
	}
}

void hashTableRemove(HashTable* table, int key) {
	int index = hashFunction(table->capacity, key);
	HashNode* current = table->buckets[index];
	HashNode* prev = NULL;
	while (current != NULL) {
		if (current->key == key) {
			if (prev == NULL) table->buckets[index] = current->next;
			else prev->next = current->next;
			free(current);
			table->size--;
			if (table->capacity > INIT_CAPACITY && table->size < table->capacity * 0.125) {
				hashTableResize(table, table->capacity / 2);
			}
			return;
		}
		prev = current;
		current = current->next;
	}
}

void hashTableTraversal(HashTable* table) {
	for (int i = 0; i < table->capacity; i++) {
		HashNode* current = table->buckets[i];
		while (current != NULL) {
			printf("%d\t", current->value);
			current = current->next;
		}
	}
	printf("\n");
}

void hashTableDelete(HashTable* table) {
	for (int i = 0; i < table->capacity; i++) {
		HashNode* current = table->buckets[i];
		while (current != NULL) {
			HashNode* next = current->next;
			free(current);
			current = next;
		}
	}
	free(table->buckets);
	free(table);
}

HashSet* initHashSet(int initCapacity) {
	HashSet* set = (HashSet*)malloc(sizeof(HashSet));
	if (!set) exit(EXIT_FAILURE);
	set->table = initHashTable(initCapacity);
	return set;
}

void hashSetPut(HashSet* set, int key, int value) {
	hashTablePut(set->table, key, value);
}

void hashSetRemove(HashSet* set, int key) {
	hashTableRemove(set->table, key);
}

bool hashSetContains(HashSet* set, int key) {
	int temp;
	return hashTableGet(set->table, key, &temp);
}

int hashSetGetSize(HashSet* set) {
	return set->table->size;
}

void hashSetDelete(HashSet* set) {
	hashTableDelete(set->table);
	free(set);
}