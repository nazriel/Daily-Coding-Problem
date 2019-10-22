#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node
{
    void* value;
    size_t size;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct XorLinkedList
{
    Node* tail;
    Node* head;
    size_t len;
} XorLinkedList;

void add(XorLinkedList *list, void *value, size_t size)
{
    (void) list;
    (void) value;
    (void) size;
}

int main()
{
    return 0;
}
