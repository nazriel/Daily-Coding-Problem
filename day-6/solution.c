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
    struct Node* xor;
} Node;

typedef struct XorLinkedList
{
    Node* tail;
    Node* head;
    size_t len;
} XorLinkedList;

XorLinkedList* newXorLinkedList()
{
    XorLinkedList* n = (XorLinkedList*) malloc(sizeof(XorLinkedList));
    if (!n)
    {
        assert(false);
    }

    memset(n, 0, sizeof(XorLinkedList));

    return n;
}

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

Node* xorNodes(Node* left, Node* right)
{
    return (Node *)(((uintptr_t)left) ^ ((uintptr_t)right));
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

void* get(XorLinkedList* list, size_t nth)
{
    if (nth > list->len)
        return NULL;

    Node* curr = list->head;
    size_t i = 0u;
    for (i = 0; i < nth && curr; i++, curr = curr->next)
    {
    }

    if (i != nth || !curr)
        return NULL;

    return curr->value;
}

void printAll(XorLinkedList* list)
{
    Node* curr = list->head;
    Node* prev = NULL;

    while (curr)
    {
        printf("%p (next: %p, prev: %p, xor: %p): %.*s\n", (void*) curr, (void*) curr->next, (void*) curr->prev,
            (void*) curr->xor, (int) curr->size, (char*) curr->value);
        prev = curr;
        curr = curr->next;
    }

    curr = prev;
    while (curr)
    {
        printf("%p (next: %p, prev: %p, xor: %p): %.*s\n", (void*) curr, (void*) curr->next, (void*) curr->prev,
            (void*) curr->xor, (int) curr->size, (char*) curr->value);
        curr = curr->prev;
    }
}

int main()
{
    XorLinkedList* list = newXorLinkedList();
    add(list, ((void*) "abcd"), 5);
    add(list, ((void*) "dcba"), 5);
    add(list, ((void*) "xvyz"), 5);

    const char* v = get(list, 2);
    assert(v != NULL && strcmp(v, "xvyz") == 0);

    v = get(list, 1);
    assert(v != NULL && strcmp(v, "dcba") == 0);

    v = get(list, 0);
    assert(v != NULL && strcmp(v, "abcd") == 0);

    printAll(list);
    return 0;
}
