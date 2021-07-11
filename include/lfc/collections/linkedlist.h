#ifndef LFC_LINKEDLIST_HEADER
#define LFC_LINKEDLIST_HEADER

#include <stdlib.h>

struct ll_node {
    struct ll_node* next;
    void* data;
};

typedef struct {
    struct ll_node* head;
    struct ll_node* tail;
    size_t len;
} list_t;

// Initialize an empty linked list
void ll_init(list_t* list);

// Free the contents of the linked list, freeing each element according to the provided destructor
// Note that the pointer to each element is not freed; the destructor must free it if necessary
// FIXME: should i be using optionals here? probably
void ll_free(list_t* list, void (*elem_free)(void*));

// Append an element to the tail of the linked list
void ll_append(list_t* list, void* elem);

// Prepend an element to the head of the linked list
void ll_prepend(list_t* list, void* elem);

// Search the linked list for the given value, returning its index if found
size_t ll_find(list_t* list, void* target, void (*elem_eq)(void*, void*));

// TODO: functional stuff

#endif
