#ifndef LFC_SET_HEADER
#define LFC_SET_HEADER

#include "lfc/collections/array.h"

typedef int (*hash_fn_t)(void*);

typedef struct {
    hash_fn_t hash_fn;
    int (*elem_eq)(void*, void*); // equality between two elements
    array_t buckets; // array of linked lists of nodes
} hash_set_t;

// Initialize a new set w/ the given hash function
void hash_set_init(hash_set_t* set, hash_fn_t hash_fn, int (*elem_eq)(void*, void*));

// Insert an element into the set
void hash_set_insert(hash_set_t* set, void* elem);

// Remove an element from the set
void hash_set_remove(hash_set_t* set, void* elem);

// Check whether or not the set contains the given element
int hash_set_contains(hash_set_t* set, void* elem);

#endif
