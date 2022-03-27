#ifndef LFC_ARRAY_HEADER
#define LFC_ARRAY_HEADER

#include <stdlib.h>

#include "lfc/utils/mem.h"

/// Fixed-size, checked array; more or less a "checked pointer". `array_t` makes no assumptions about how memory
/// is allocated, but does perform bounds checking to ensure that accesses are within the bounds of the array,
/// and does provide a simple search mechanism.

typedef struct {
    void* data;
    size_t len;
    size_t elem_size;
} array_t;

// Initialize the array with the given contents
void array_init(array_t* array, void* data, size_t len, size_t elem_size);

// Free the contents of the array
void array_free(array_t* array, free_fn_t elem_free);

// Retrieve a pointer to the value at the given index in the array
// Panics if the index is out of bounds
void* array_at(array_t* array, size_t index);

// Search the array for the given element
// Returns the appropriate index if it exists, otherwise (size_t)-1
// `elem_eq()` must return 1 if the two elements are equal, otherwise it must return 0
size_t array_find(array_t* array, void* elem, int (*elem_eq)(void*, void*));

// TODO: functional stuff

typedef struct {
    array_t base;
} dynarray_t;

// Initialize the array with a dynamically allocated of the given size
void dynarray_init(dynarray_t* array, size_t len, size_t elem_size);

// Free the contentes of the array
void dynarray_free(dynarray_t* array, free_fn_t elem_free);

// Retrieve the length of the array
size_t dynarray_len(dynarray_t* array);

// Retrieve the size of the elements in the array
size_t dynarray_elem_size(dynarray_t* array);

// Retrieve a pointer to the value at the given index in the array
// Panics if the index is out of bounds
void* dynarray_at(dynarray_t* array, size_t index);

// Search the array for the given element
// Returns the index of the element if it exists, otherwise (size_t)-1
// `elem_eq()` must return 1 if the two elements are equal, otherwise 0
size_t dynarray_find(dynarray_t* array, void* elem, int (*elem_eq)(void*, void*));

#endif
