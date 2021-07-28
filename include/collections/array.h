#ifndef LFC_ARRAY_HEADER
#define LFC_ARRAY_HEADER

#include <stdlib.h>

// QUIP: is array useless, or at least not useful enough to just its existence rn
//       solution: implicit allocation, so that the array manages its own heap-allocated data

// Fixed-size, checked array
typedef struct {
    void* data;
    size_t len;
    size_t elem_size;
} array_t;

// Initialize the array with the given contents
void array_init(array_t* array, void* data, size_t len, size_t elem_size);

// Free the contents of the array
void array_free(array_t* array, void (*elem_free)(void*));

// Retrieve a pointer to the value at the given index in the array
// Panics if the index is out of bounds
void* array_get(array_t* array, size_t index);

// Set the value of the element at the given index in the array
// If a cleanup routine is provided, it is executed on the existing value before overwriting it
// NOTE: the element is added to the array through a byte-by-byte copy into the appropriate spot in memory
void array_set(array_t* array, size_t index, void* data, void (*elem_free)(void*));

// Search the array for the given element
// Returns the appropriate index if it exists, otherwise null
// `elem_eq()` must return 1 if the two elements are equal, otherwise it must return 0
size_t array_find(array_t* array, void* elem, int (*elem_eq)(void*, void*));

// TODO: functional stuff

#endif
