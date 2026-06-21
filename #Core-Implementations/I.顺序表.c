#include <stdio.h>
#include <stdlib.h>

typedef struct seqlist SeqList;
struct seqlist {
	int* data;
	int size;
	int cap;
};

const int INIT_CAP = 4;

SeqList* initSeqList();
void AddAtHead(SeqList* list, int val);
void AddAtTail(SeqList* list, int val);
void AddAtIndex(SeqList* list, int val, int index);
void DeleteAtIndex(SeqList* list, int index);
void Modify(SeqList* list, int val, int index);
int Get(SeqList* list, int index);
void traverse(SeqList* list);
void DeleteList(SeqList* list);
int* expand(SeqList* list);
int* shrink(SeqList* list);

int main(int argc, const char* argv[]) {
	//测试脚本
	SeqList* list = initSeqList();
	AddAtTail(list, 5);
	AddAtTail(list, 7);
	AddAtTail(list, 15);
	AddAtTail(list, 8);
	AddAtTail(list, 19);
	AddAtHead(list, 21);
	traverse(list);
	AddAtIndex(list, 27, 2);
	traverse(list);
	DeleteAtIndex(list, 4);
	traverse(list);
	Modify(list, 30, 1);
	traverse(list);
	DeleteAtIndex(list, 1);
	DeleteAtIndex(list, 1);
	DeleteAtIndex(list, 1);
	traverse(list);
	printf("%d\n", Get(list, 0));
	DeleteList(list);
}

SeqList* initSeqList() {
	SeqList* list = (SeqList*)malloc(sizeof(SeqList));
	if (!list) exit(EXIT_FAILURE);
	list->data = (int*)malloc(sizeof(int) * INIT_CAP);
	if (!list->data) exit(EXIT_FAILURE);
	//for (int i = 0; i < INIT_CAP; i++) list->data[i] = 0;
	list->size = 0;
	list->cap = INIT_CAP;
	return list;
}

void AddAtHead(SeqList* list, int val) {
	if (list->size == list->cap) list->data = expand(list);
	for (int i = list->size; i > 0; i--) list->data[i] = list->data[i - 1];
	list->data[0] = val;
	list->size += 1;
}

void AddAtTail(SeqList* list, int val) {
	if (list->size == list->cap) list->data = expand(list);
	list->data[list->size] = val;
	list->size += 1;
}

void AddAtIndex(SeqList* list, int val, int index) {
	if (list->size == list->cap) list->data = expand(list);
	if (index < 0 || index>list->size) exit(EXIT_FAILURE);
	for (int i = list->size; i > index; i--) list->data[i] = list->data[i - 1];
	list->data[index] = val;
	list->size += 1;
}

void DeleteAtIndex(SeqList* list, int index) {
	if (list->size <= 0.5 * list->cap && list->cap > INIT_CAP) list->data = shrink(list);
	if (index < 0 || index >= list->size) exit(EXIT_FAILURE);
	for (int i = index; i < list->size-1; i++) list->data[i] = list->data[i + 1];
	list->size -= 1;
}

void Modify(SeqList* list, int val, int index) {
	if (index < 0 || index >= list->size) exit(EXIT_FAILURE);
	list->data[index] = val;
}

int Get(SeqList* list, int index) {
	if (index < 0 || index >= list->size) exit(EXIT_FAILURE);
	return list->data[index];
}

void traverse(SeqList* list) {
	for (int i = 0; i < list->size; i++) printf("%d\t", list->data[i]);
	printf("\n");
}

void DeleteList(SeqList* list) {
	free(list->data);
	free(list);
}

int* expand(SeqList* list) {
	int* newarray = (int*)malloc(sizeof(int) * list->cap * 2);
	if (!newarray) exit(EXIT_FAILURE);
	list->cap *= 2;
	for (int i = 0; i < list->size; i++) newarray[i] = list->data[i];
	//for (int i = list->size; i < list->cap; i++) newarray[i] = 0;
	free(list->data);
	return newarray;
}

int* shrink(SeqList* list) {
	int* newarray = (int*)malloc(sizeof(int) * list->cap * 0.5);
	if (!newarray) exit(EXIT_FAILURE);
	list->cap /= 2;
	for (int i = 0; i < list->size; i++) newarray[i] = list->data[i];
	free(list->data);
	return newarray;
}