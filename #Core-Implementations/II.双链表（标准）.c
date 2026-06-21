#include <stdio.h>
#include <stdlib.h>

typedef struct MyLinkedList MyLinkedList;
typedef struct Node Node;

struct Node {
    int val;
    Node* prev;
    Node* next;
};

struct MyLinkedList {
    Node* head;
    Node* tail;
    int size;
};

MyLinkedList* myLinkedListCreate();
int myLinkedListGet(MyLinkedList* obj, int index);
void myLinkedListAddAtHead(MyLinkedList* obj, int val);
void myLinkedListAddAtTail(MyLinkedList* obj, int val);
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val);
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index);
void myLinkedListTraverse(MyLinkedList* obj);
void myLinkedListModify(MyLinkedList* obj, int index, int val);
void myLinkedListFree(MyLinkedList* obj);

int main(int argc, const char* argv[])
{
    //²âÊÔ½Å±¾
    MyLinkedList* list = myLinkedListCreate();
    myLinkedListAddAtHead(list, 13);
    myLinkedListAddAtHead(list, 18);
    myLinkedListAddAtTail(list, 25);
    myLinkedListAddAtIndex(list, 1, 14);
    myLinkedListTraverse(list);
    myLinkedListModify(list, 1, 30);
    myLinkedListDeleteAtIndex(list, 3);
    myLinkedListTraverse(list);
    printf("%d\n", myLinkedListGet(list, 0));
    myLinkedListFree(list);
}

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* obj = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    if (!obj)exit(EXIT_FAILURE);
    obj->size = 0;
    obj->head = (Node*)malloc(sizeof(Node));
    if (!obj->head)exit(EXIT_FAILURE);
    obj->tail = (Node*)malloc(sizeof(Node));
    if (!obj->tail)exit(EXIT_FAILURE);
    obj->head->prev = NULL;
    obj->head->next = obj->tail;
    obj->tail->next = NULL;
    obj->tail->prev = obj->head;
    return obj;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    if (index >= obj->size || index < 0) exit(EXIT_FAILURE);
    Node* ptr = obj->head->next;
    for (int i = 0; i < index; i++) ptr = ptr->next;
    return ptr->val;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) exit(EXIT_FAILURE);
    newnode->val = val;
    newnode->next = obj->head->next;
    obj->head->next->prev = newnode;
    obj->head->next = newnode;
    newnode->prev = obj->head;
    obj->size += 1;
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) exit(EXIT_FAILURE);
    newnode->val = val;
    newnode->prev = obj->tail->prev;
    obj->tail->prev->next = newnode;
    newnode->next = obj->tail;
    obj->tail->prev = newnode;
    obj->size += 1;
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    if (index > obj->size || index < 0) exit(EXIT_FAILURE);
    Node* ptr = obj->head;
    for (int i = 0; i < index; i++) ptr = ptr->next;
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) exit(EXIT_FAILURE);
    newnode->val = val;
    newnode->next = ptr->next;
    ptr->next->prev = newnode;
    ptr->next = newnode;
    newnode->prev = ptr;
    obj->size += 1;
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    if (index >= obj->size || index < 0) exit(EXIT_FAILURE);
    Node* ptr = obj->head;
    for (int i = 0; i < index; i++) ptr = ptr->next;
    Node* temp = ptr->next;
    temp->next->prev = ptr;
    ptr->next = temp->next;
    free(temp);
    obj->size -= 1;
}

void myLinkedListTraverse(MyLinkedList* obj) {
    Node* ptr = obj->head;
    while (ptr->next != obj->tail)
    {
        ptr = ptr->next;
        printf("%d\t", ptr->val);
    }
    printf("\n");
}

void myLinkedListModify(MyLinkedList* obj, int index, int val) {
    if (index >= obj->size || index < 0) exit(EXIT_FAILURE);
    Node* ptr = obj->head->next;
    for (int i = 0; i < index; i++) ptr = ptr->next;
    ptr->val = val;
}

void myLinkedListFree(MyLinkedList* obj) {
    Node* fast = obj->head->next;
    Node* slow = obj->head;
    while (fast != obj->tail)
    {
        slow = fast;
        fast = fast->next;
        free(slow);
    }
    free(obj->head);
    free(obj->tail);
    free(obj);
}