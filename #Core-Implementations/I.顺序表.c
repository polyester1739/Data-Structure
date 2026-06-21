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
void SeqListAddAtHead(SeqList* list, int val);
void SeqListAddAtTail(SeqList* list, int val);
void SeqListAddAtIndex(SeqList* list, int val, int index);
void SeqListRemoveAtIndex(SeqList* list, int index);
void SeqListSet(SeqList* list, int val, int index);
int SeqListGet(SeqList* list, int index);
void SeqListTraverse(SeqList* list);
void SeqListDelete(SeqList* list);
int* expand(SeqList* list);
int* shrink(SeqList* list);

int main(int argc, const char* argv[]) {
	//测试脚本
	SeqList* list = initSeqList();
	SeqListAddAtTail(list, 5);
	SeqListAddAtTail(list, 7);
	SeqListAddAtTail(list, 15);
	SeqListAddAtTail(list, 8);
	SeqListAddAtTail(list, 19);
	SeqListAddAtHead(list, 21);
	SeqListTraverse(list);
	SeqListAddAtIndex(list, 27, 2);
	SeqListTraverse(list);
	SeqListRemoveAtIndex(list, 4);
	SeqListTraverse(list);
	SeqListSet(list, 30, 1);
	SeqListTraverse(list);
	SeqListRemoveAtIndex(list, 1);
	SeqListRemoveAtIndex(list, 1);
	SeqListRemoveAtIndex(list, 1);
	SeqListTraverse(list);
	printf("%d\n", SeqListGet(list, 0));
	SeqListDelete(list);
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

void SeqListAddAtHead(SeqList* list, int val) {
	if (list->size == list->cap) list->data = expand(list);
	for (int i = list->size; i > 0; i--) list->data[i] = list->data[i - 1];
	list->data[0] = val;
	list->size += 1;
}

void SeqListAddAtTail(SeqList* list, int val) {
	if (list->size == list->cap) list->data = expand(list);
	list->data[list->size] = val;
	list->size += 1;
}

void SeqListAddAtIndex(SeqList* list, int val, int index) {
	if (list->size == list->cap) list->data = expand(list);
	if (index < 0 || index>list->size) exit(EXIT_FAILURE);
	for (int i = list->size; i > index; i--) list->data[i] = list->data[i - 1];
	list->data[index] = val;
	list->size += 1;
}

void SeqListRemoveAtIndex(SeqList* list, int index) {
	if (list->size <= 0.5 * list->cap && list->cap > INIT_CAP) list->data = shrink(list);
	if (index < 0 || index >= list->size) exit(EXIT_FAILURE);
	for (int i = index; i < list->size-1; i++) list->data[i] = list->data[i + 1];
	list->size -= 1;
}

void SeqListSet(SeqList* list, int val, int index) {
	if (index < 0 || index >= list->size) exit(EXIT_FAILURE);
	list->data[index] = val;
}

int SeqListGet(SeqList* list, int index) {
	if (index < 0 || index >= list->size) exit(EXIT_FAILURE);
	return list->data[index];
}

void SeqListTraverse(SeqList* list) {
	for (int i = 0; i < list->size; i++) printf("%d\t", list->data[i]);
	printf("\n");
}

void SeqListDelete(SeqList* list) {
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