#ifndef LFC_SET_HEADER
#define LFC_SET_HEADER

#include "lfc/collections/array.h"
#include "lfc/utils/hash.h"

#include <stdlib.h>

#define MAX_LOAD_FACTOR 0.5
#define DEFAULT_BUCKETS (size_t)20

typedef struct {
    hash_fn_t hash_fn;
    int (*elem_eq)(void*, void*); // equality between two elements
    array_t buckets; // the actual array never expands so a vector is unnecessary
    size_t size;
} hashset_t;

// Initialize a new set w/ the given hash function
void hashset_init(hashset_t* set, size_t n_buckets, hash_fn_t hash_fn, int (*elem_eq)(void*, void*));

// Free the contents of the set
// Elements are not assumed to be dynamically allocated, so they must be freed manually if necessary
void hashset_free(hashset_t* set, void (*elem_free)(void*));

// Insert an element into the set
void hashset_insert(hashset_t* set, void* elem);

// Remove an element from the set
void hashset_remove(hashset_t* set, void* elem, void (*elem_free)(void*));

// Check whether or not the set contains the given element
int hashset_contains(hashset_t* set, void* elem);

// Check whether or not the set is empty
int hashset_is_empty(hashset_t* set);

// Calculate the load factor for the set
double hashset_load_factor(hashset_t* set);

// TODO: tree set

#endif
