#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList LinkedList;
typedef struct Node Node;

struct Node {
    int val;
    Node* next;
};

struct LinkedList {
    int size;
    Node* head;
    Node* tail;
};

LinkedList* initLinkedList();
int LinkedListGet(LinkedList* list, int index);
void LinkedListAddAtHead(LinkedList* list, int val);
void LinkedListAddAtTail(LinkedList* list, int val);
void LinkedListAddAtIndex(LinkedList* list, int index, int val);
void LinkedListRemoveAtIndex(LinkedList* list, int index);
void LinkedListTraverse(LinkedList* list);
void LinkedListSet(LinkedList* list, int index, int val);
void LinkedListDelete(LinkedList* list);

int main(int argc, const char* argv[]) {
    //²âÊÔ½Å±¾
    LinkedList* list = initLinkedList();
    LinkedListAddAtHead(list, 13);
    LinkedListAddAtHead(list, 18);
    LinkedListAddAtTail(list, 25);
    LinkedListAddAtIndex(list, 1, 14);
    LinkedListTraverse(list);
    LinkedListSet(list, 1, 30);
    LinkedListRemoveAtIndex(list, 3);
    LinkedListTraverse(list);
    printf("%d\n", LinkedListGet(list, 0));
    LinkedListDelete(list);
}

LinkedList* initLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) exit(EXIT_FAILURE);
    list->size = 0;
    list->head = (Node*)malloc(sizeof(Node));
    if (!list->head) exit(EXIT_FAILURE);
    list->tail = list->head;
    list->head->next = NULL;
    return list;
}

int LinkedListGet(LinkedList* list, int index) {
    if (index >= list->size || index < 0) exit(EXIT_FAILURE);
    Node* ptr = list->head->next;
    for (int i = 0; i < index; i++) ptr = ptr->next;
    return ptr->val;
}

void LinkedListAddAtHead(LinkedList* list, int val) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) exit(EXIT_FAILURE);
    newnode->val = val;
    newnode->next = list->head->next;
    list->head->next = newnode;
	if (list->size == 0) list->tail = newnode;
    list->size += 1;
}

void LinkedListAddAtTail(LinkedList* list, int val) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) exit(EXIT_FAILURE);
    newnode->val = val;
    newnode->next = NULL;
    list->tail->next = newnode;
    list->tail = newnode;
    list->size += 1;
}

void LinkedListAddAtIndex(LinkedList* list, int index, int val) {
    if (index > list->size || index < 0) exit(EXIT_FAILURE);
    Node* ptr = list->head;
    for (int i = 0; i < index; i++) ptr = ptr->next;
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) exit(EXIT_FAILURE);
    newnode->val = val;
    newnode->next = ptr->next;
    ptr->next = newnode;
    list->size += 1;
}

void LinkedListRemoveAtIndex(LinkedList* list, int index) {
    if (index >= list->size || index < 0) exit(EXIT_FAILURE);
    Node* ptr = list->head;
    for (int i = 0; i < index; i++) ptr = ptr->next;
    Node* temp = ptr->next;
    ptr->next = temp->next;
    free(temp);
    list->size -= 1;
}

void LinkedListTraverse(LinkedList* list) {
    Node* ptr = list->head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
        printf("%d\t", ptr->val);
    }
    printf("\n");
}

void LinkedListSet(LinkedList* list, int index, int val) {
    if (index >= list->size || index < 0) exit(EXIT_FAILURE);
    Node* ptr = list->head->next;
    for (int i = 0; i < index; i++) ptr = ptr->next;
    ptr->val = val;
}

void LinkedListDelete(LinkedList* list) {
    Node* fast = list->head->next;
    Node* slow = list->head;
    while (fast != NULL) {
        slow = fast;
        fast = fast->next;
        free(slow);
    }
    free(list->head);
    free(list);
}