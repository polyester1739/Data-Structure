#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList LinkedList;
typedef struct Node Node;

struct Node {
    int val;
    Node* prev;
    Node* next;
};

struct LinkedList {
    Node* head;
    Node* tail;
    int size;
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
    if (!list)exit(EXIT_FAILURE);
    list->size = 0;
    list->head = (Node*)malloc(sizeof(Node));
    if (!list->head)exit(EXIT_FAILURE);
    list->tail = (Node*)malloc(sizeof(Node));
    if (!list->tail)exit(EXIT_FAILURE);
    list->head->prev = NULL;
    list->head->next = list->tail;
    list->tail->next = NULL;
    list->tail->prev = list->head;
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
    list->head->next->prev = newnode;
    list->head->next = newnode;
    newnode->prev = list->head;
    list->size += 1;
}

void LinkedListAddAtTail(LinkedList* list, int val) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) exit(EXIT_FAILURE);
    newnode->val = val;
    newnode->prev = list->tail->prev;
    list->tail->prev->next = newnode;
    newnode->next = list->tail;
    list->tail->prev = newnode;
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
    ptr->next->prev = newnode;
    ptr->next = newnode;
    newnode->prev = ptr;
    list->size += 1;
}

void LinkedListRemoveAtIndex(LinkedList* list, int index) {
    if (index >= list->size || index < 0) exit(EXIT_FAILURE);
    Node* ptr = list->head;
    for (int i = 0; i < index; i++) ptr = ptr->next;
    Node* temp = ptr->next;
    temp->next->prev = ptr;
    ptr->next = temp->next;
    free(temp);
    list->size -= 1;
}

void LinkedListTraverse(LinkedList* list) {
    Node* ptr = list->head;
    while (ptr->next != list->tail) {
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
    while (fast != list->tail) {
        slow = fast;
        fast = fast->next;
        free(slow);
    }
    free(list->head);
    free(list->tail);
    free(list);
}