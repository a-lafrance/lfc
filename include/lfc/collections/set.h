#ifndef LFC_SET_HEADER
#define LFC_SET_HEADER

#include "lfc/collections/array.h"

#include <stdlib.h>

typedef int (*hash_fn_t)(void*);

typedef struct {
    hash_fn_t hash_fn;
    int (*elem_eq)(void*, void*); // equality between two elements
    array_t buckets; // TODO: make vec
    size_t size;
} hashset_t;

// Initialize a new set w/ the given hash function
void hashset_init(hashset_t* set, hash_fn_t hash_fn, int (*elem_eq)(void*, void*));

// Free the contents of the set
// Because elements are assumed to be dynamically allocated, element pointers are automatically freed by this function, so
//   the provided element cleanup function must only free the contents of each element, not the pointers themselves
void hashset_free(hashset_t* set, void (*elem_free)(void*));

// Insert an element into the set
void hashset_insert(hashset_t* set, void* elem);

// Remove an element from the set
void hashset_remove(hashset_t* set, void* elem);

// Check whether or not the set contains the given element
int hashset_contains(hashset_t* set, void* elem);

// Calculate the load factor for the set
double hashset_load_factor(hashset_t* set);

#endif
