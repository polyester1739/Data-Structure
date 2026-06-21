#include <stdio.h>
#include <stdlib.h>

typedef struct HashNode HashNode;

struct HashNode {
    int key;
    int value;
    HashNode* next;
};

int main(int argc, const char* argv[])
{

}

HashNode* initHashTable()
{
    HashNode* hashtable = (HashNode*)malloc(sizeof(HashNode));
    if (!hashtable) exit(EXIT_FAILURE);

}