#ifndef LFC_ARRAY_HEADER
#define LFC_ARRAY_HEADER

#include <stdlib.h>

// Fixed-size, checked array
typedef struct {
    void* data;
    size_t len;
    size_t elem_size;
} array_t;

// Initialize a new, empty array
void array_new(array_t* array, size_t elem_size);

// Initialize the array with the given contents
void array_init(array_t* array, void* data, size_t len, size_t elem_size);

// Free the contents of the array
void array_free(array_t* array, void (*elem_free)(void*));

// Retrieve a pointer to the value at the given index in the array
// Panics if the index is out of bounds
void* array_get(array_t* array, size_t index);

// Search the array for the given element
// Returns the appropriate index if it exists, otherwise null
// `elem_eq()` must return 1 if the two elements are equal, otherwise it must return 0
size_t array_find(array_t* array, void* elem, int (*elem_eq)(void*, void*));

// TODO: functional stuff

#endif
