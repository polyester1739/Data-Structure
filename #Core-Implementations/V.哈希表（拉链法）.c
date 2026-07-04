#include <stdio.h>
#include <stdlib.h>

typedef struct HashNode HashNode;
typedef struct HashTable HashTable;

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

const int INIT_CAPACITY = 6;

int hashFunction(HashTable* table, int key);
HashNode* initHashTable(int initCapacity);
int hashTableGet(HashTable* table, int key);
void hashTablePut(HashTable* table, int key, int value);
void hashTableRemove(HashTable* table, int key);
void hashTableResize(HashTable* table, int newCapacity);
void hashTableTraversal(HashTable* table);
void hashTableDelete(HashTable* table);

int main(int argc, const char* argv[]) {
	HashTable* table = initHashTable(INIT_CAPACITY);
	hashTablePut(table, 0, 10);
	hashTablePut(table, 25, 20);
	hashTablePut(table, 50, 30);
	hashTablePut(table, 75, 40);
	hashTablePut(table, 13, 50);
	hashTablePut(table, 26, 60);
	hashTablePut(table, 39, 70);
	hashTablePut(table, 52, 80);
	hashTableTraversal(table);
	hashTableRemove(table, 25);
	hashTableRemove(table, 50);
	hashTableRemove(table, 13);
	hashTableRemove(table, 39);
	hashTableTraversal(table);
	printf("Key 75: %d\n", hashTableGet(table, 75));
	printf("Key 25: %d\n", hashTableGet(table, 25));
	hashTableDelete(table);
}

int hashFunction(HashTable* table, int key) {
	return (key & 0x7FFFFFFF) % table->capacity;
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