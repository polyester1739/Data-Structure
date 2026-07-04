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
	HashNode** hashTable;
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
	printf("Contains 75: %d\n", hashSetContains(set, 75));
	printf("Contains 25: %d\n", hashSetContains(set, 25));
	hashSetDelete(set);
}

int hashFunction(HashTable* table, int key) {
	return (key & 0x7FFFFFFF) % table->capacity;
}

void hashTableResize(HashTable* table, int newCapacity) {
	if (newCapacity <= 0) newCapacity = 1;
	HashNode** newTable = (HashNode**)calloc(newCapacity, sizeof(HashNode*));
	if (!newTable) exit(EXIT_FAILURE);

	for (int i = 0; i < table->capacity; i++) {
		HashNode* current = table->hashTable[i];
		while (current != NULL) {
			HashNode* next = current->next;
			int newIndex = (current->key & 0x7FFFFFFF) % newCapacity;
			current->next = newTable[newIndex];
			newTable[newIndex] = current;
			current = next;
		}
	}

	free(table->hashTable);
	table->hashTable = newTable;
	table->capacity = newCapacity;
}

HashNode* initHashTable(int initCapacity) {
	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	if (!table) exit(EXIT_FAILURE);
	table->size = 0;
	if (initCapacity <= 0) table->capacity = 1;
	else table->capacity = initCapacity;
	table->hashTable = (HashNode**)calloc(table->capacity, sizeof(HashNode*));
	if (!table->hashTable) exit(EXIT_FAILURE);
	return table;
}

int hashTableGet(HashTable* table, int key) {
	int index = hashFunction(table, key);
	HashNode* current = table->hashTable[index];
	while (current != NULL) {
		if (current->key == key) return current->value;
		current = current->next;
	}
	return -1; // Key not found
}

void hashTablePut(HashTable* table, int key, int value) {
	int index = hashFunction(table, key);
	HashNode* current = table->hashTable[index];
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
	newNode->next = table->hashTable[index];
	table->hashTable[index] = newNode;
	table->size++;

	if (table->size > table->capacity * 0.75) hashTableResize(table, table->capacity * 2);
}

void hashTableRemove(HashTable* table, int key) {
	int index = hashFunction(table, key);
	HashNode* current = table->hashTable[index];
	HashNode* prev = NULL;
	while (current != NULL) {
		if (current->key == key) {
			if (prev == NULL) table->hashTable[index] = current->next;
			else prev->next = current->next;
			free(current);
			table->size--;
			if (table->size < table->capacity * 0.25) hashTableResize(table, table->capacity / 2);
			return;
		}
		prev = current;
		current = current->next;
	}
}

void hashTableTraversal(HashTable* table) {
	for (int i = 0; i < table->capacity; i++) {
		HashNode* current = table->hashTable[i];
		while (current != NULL) {
			printf("%d\t", current->value);
			current = current->next;
		}
	}
	printf("\n");
}

void hashTableDelete(HashTable* table) {
	for (int i = 0; i < table->capacity; i++) {
		HashNode* current = table->hashTable[i];
		while (current != NULL) {
			HashNode* next = current->next;
			free(current);
			current = next;
		}
	}
	free(table->hashTable);
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
	return hashTableGet(set->table, key) != -1;
}

int hashSetGetSize(HashSet* set) {
	return set->table->size;
}

void hashSetDelete(HashSet* set) {
	hashTableDelete(set->table);
	free(set);
}