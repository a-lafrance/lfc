#ifndef LFC_LINKEDLIST_HEADER
#define LFC_LINKEDLIST_HEADER

#include <stdlib.h>

/// Implements a simple, singly-linked list. Elements can be inspected & inserted
/// from the front & back of the list. Simple search & removal is also provided.

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
// Note that the actual data pointer is not freed; the destructor must free it if necessary
void ll_free(list_t* list, void (*elem_free)(void*));

// Returns a pointer to the first element of the list, if it exists
void* ll_first(list_t* list);

// Returns a pointer to the last element of the list, if it exists
void* ll_last(list_t* list);

// Append an element to the tail of the linked list
void ll_append(list_t* list, void* elem);

// Prepend an element to the head of the linked list
void ll_prepend(list_t* list, void* elem);

// Pop the first element off the list, or null if the list is empty
void* ll_pop_first(list_t* list);

// Return whether or not the linked list contains the given value
int ll_find(list_t* list, void* target, int (*elem_eq)(void*, void*));

// Remove the element that equals the given target, if found
void* ll_remove(list_t* list, void* target, int (*elem_eq)(void*, void*));

// Check whether or not the list is empty
int ll_is_empty(list_t* list);

// TODO: functional stuff

#endif
