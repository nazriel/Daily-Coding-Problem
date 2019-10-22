#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

Node* newNode(void* value, size_t size)
{
    Node* n = (Node*) malloc(sizeof(Node));
    if (!n)
    {
        assert(false);
    }

    memset(n, 0, sizeof(Node));
    n->value = value;
    n->size = size;

    return n;
}
void add(XorLinkedList* list, void *value, size_t size)
{
    Node* n = newNode(value, size);
    if (list->head == NULL)
{
        list->head = n;
        list->tail = n;
        list->len = 1;
        return;
    }
    list->tail->next = n;
    n->prev = list->tail;

    list->tail = n;
    list->len++;
}

void* get(XorLinkedList* list, size_t index)
{
    (void) index;
    (void) list;
    return (void *)0xdeadbeef;
}

void printAll(XorLinkedList* list)
{
    Node* curr = list->head;
    Node* prev = NULL;

    while (curr)
    {
        printf("%p (next: %p, prev: %p): %.*s\n", (void*) curr, (void*) curr->next, (void*) curr->prev, (int) curr->size, (char*) curr->value);
        prev = curr;
        curr = curr->next;
    }

    curr = prev;
    while (curr)
    {
        printf("%p (next: %p, prev: %p): %.*s\n", (void*) curr, (void*) curr->next, (void*) curr->prev, (int) curr->size, (char*) curr->value);
        curr = curr->prev;
    }
}

int main()
{
    return 0;
}
