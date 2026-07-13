#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

const int INIT_CAPACITY = 6;

typedef struct KV KV;
typedef struct HashNode HashNode;
typedef struct ArrayHashMap ArrayHashMap;

struct KV {
	int key;
	int value;
};

struct HashNode {
	int key;
	int index;
	HashNode* next;
};

struct ArrayHashMap {
	HashNode** buckets;
	KV* array;
	int size;
	int arrayCapacity;
	int mapCapacity;
};

int hashFunction(int key, int capacity);
ArrayHashMap* initArrayHashMap();
bool arrayHashMapGet(ArrayHashMap* map, int key, int* result);
void arrayHashMapPut(ArrayHashMap* map, int key, int value);
void arrayHashMapRemove(ArrayHashMap* map, int key);
void hashMapResize(ArrayHashMap* map, int newCapacity);
void arrayResize(ArrayHashMap* map, int newCapacity);
void arrayHashMapTraversal(ArrayHashMap* map);
bool arrayHashMapGetRandom(ArrayHashMap* map, int* result);
void arrayHashMapDelete(ArrayHashMap* map);

int main(int argc, const char* argv[]) {
	srand((unsigned int)time(NULL));

	int temp;
	ArrayHashMap* map = initArrayHashMap();
	
	if (arrayHashMapGetRandom(map, &temp)) printf("Random value: %d\n", temp);
	else printf("The map is empty.\n");

	arrayHashMapPut(map, 0, 10);
	arrayHashMapPut(map, 25, 20);
	arrayHashMapPut(map, 50, 30);
	arrayHashMapPut(map, 75, 40);
	arrayHashMapPut(map, 13, 50);
	arrayHashMapPut(map, 26, 60);
	arrayHashMapPut(map, 39, 70);
	arrayHashMapPut(map, 52, 80);
	arrayHashMapTraversal(map);
	arrayHashMapRemove(map, 25);
	arrayHashMapRemove(map, 50);
	arrayHashMapRemove(map, 13);
	arrayHashMapRemove(map, 39);
	arrayHashMapTraversal(map);

	if (arrayHashMapGet(map, 75, &temp)) printf("Key 75: %d\n", temp);
	else printf("Key 75 not found.\n");
	if (arrayHashMapGet(map, 25, &temp)) printf("Key 25: %d\n", temp);
	else printf("Key 25 not found.\n");
	if (arrayHashMapGetRandom(map, &temp)) printf("Random value: %d\n", temp);
	else printf("The map is empty.\n");

	arrayHashMapDelete(map);
}

int hashFunction(int key, int capacity) {
	return (key & 0x7FFFFFFF) % capacity;
}

ArrayHashMap* initArrayHashMap() {
	ArrayHashMap* map = (ArrayHashMap*)malloc(sizeof(ArrayHashMap));
	if (!map) exit(EXIT_FAILURE);
	map->buckets = (HashNode**)calloc(INIT_CAPACITY, sizeof(HashNode*));
	if (!map->buckets) exit(EXIT_FAILURE);
	map->array = (KV*)malloc(INIT_CAPACITY * sizeof(KV));
	if (!map->array) exit(EXIT_FAILURE);
	map->size = 0;
	map->arrayCapacity = INIT_CAPACITY;
	map->mapCapacity = INIT_CAPACITY;
	return map;
}

bool arrayHashMapGet(ArrayHashMap* map, int key, int* result) {
	int index = hashFunction(key, map->mapCapacity);
	HashNode* cur = map->buckets[index];
	while (cur != NULL) {
		if (cur->key == key) {
			*result = map->array[cur->index].value;
			return true;
		}
		cur = cur->next;
	}
	return false;	// Key not found
}

void arrayHashMapPut(ArrayHashMap* map, int key, int value) {
	int index = hashFunction(key, map->mapCapacity);
	HashNode* cur = map->buckets[index];
	while (cur != NULL) {
		if (cur->key == key) {
			map->array[cur->index].value = value;
			return;
		}
		cur = cur->next;
	}

	HashNode* newnode = (HashNode*)malloc(sizeof(HashNode));
	if (!newnode) exit(EXIT_FAILURE);
	newnode->key = key;
	newnode->index = map->size;
	newnode->next = map->buckets[index];
	map->buckets[index] = newnode;
	map->array[map->size].key = key;
	map->array[map->size].value = value;
	map->size++;

	if (map->size > map->mapCapacity * 0.75) {
		hashMapResize(map, map->mapCapacity * 2);
	}

	if (map->size >= map->arrayCapacity) {
		arrayResize(map, map->arrayCapacity * 2);
	}
}

void arrayHashMapRemove(ArrayHashMap* map, int key) {
	if (map->size == 0) return;

	int index = hashFunction(key, map->mapCapacity);
	HashNode* cur = map->buckets[index];
	HashNode* prev = NULL;
	int targetIndex;
	while (cur != NULL) {
		if (cur->key == key) {
			if (prev == NULL) map->buckets[index] = cur->next;
			else prev->next = cur->next;
			targetIndex = cur->index;
			free(cur);
			if (targetIndex != map->size - 1) {
				map->array[targetIndex] = map->array[map->size - 1];
				int lastIndex = hashFunction(map->array[map->size - 1].key, map->mapCapacity);
				HashNode* lastNode = map->buckets[lastIndex];
				while (lastNode != NULL) {
					if (lastNode->key == map->array[map->size - 1].key) {
						lastNode->index = targetIndex;
						break;
					}
					lastNode = lastNode->next;
				}
			}
			map->size--;

			if (map->size < map->mapCapacity * 0.125 && map->mapCapacity > INIT_CAPACITY) {
				hashMapResize(map, map->mapCapacity / 2);
			}

			if (map->size < map->arrayCapacity * 0.5 && map->arrayCapacity > INIT_CAPACITY) {
				arrayResize(map, map->arrayCapacity / 2);
			}
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}

void hashMapResize(ArrayHashMap* map, int newCapacity) {
	if (newCapacity <= 0) newCapacity = 1;
	HashNode** newBuckets = (HashNode**)calloc(newCapacity, sizeof(HashNode*));
	if (!newBuckets) exit(EXIT_FAILURE);

	for (int i = 0; i < map->mapCapacity; i++) {
		HashNode* cur = map->buckets[i];
		while (cur != NULL) {
			HashNode* nextNode = cur->next;
			int newIndex = hashFunction(cur->key, newCapacity);
			cur->next = newBuckets[newIndex];
			newBuckets[newIndex] = cur;
			cur = nextNode;
		}
	}

	free(map->buckets);
	map->buckets = newBuckets;
	map->mapCapacity = newCapacity;
}

void arrayResize(ArrayHashMap* map, int newCapacity) {
	if (newCapacity <= 0) newCapacity = 1;
	KV* newArray = (KV*)malloc(sizeof(KV) * newCapacity);
	if (!newArray) exit(EXIT_FAILURE);

	for (int i = 0; i < map->size; i++) newArray[i] = map->array[i];

	free(map->array);
	map->array = newArray;
	map->arrayCapacity = newCapacity;
}

void arrayHashMapTraversal(ArrayHashMap* map) {
	for (int i = 0; i < map->size; i++) printf("%d\t", map->array[i].value);
	printf("\n");
}

bool arrayHashMapGetRandom(ArrayHashMap* map, int* result) {
	if (map->size == 0) return false;
	int randomIndex = rand() % map->size;
	*result = map->array[randomIndex].value;
	return true;
}

void arrayHashMapDelete(ArrayHashMap* map) {
	for (int i = 0; i < map->mapCapacity; i++) {
		HashNode* cur = map->buckets[i];
		while (cur != NULL) {
			HashNode* nextNode = cur->next;
			free(cur);
			cur = nextNode;
		}
	}
	free(map->array);
	free(map->buckets);
	free(map);
}