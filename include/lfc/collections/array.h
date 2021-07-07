#ifndef LFC_ARRAY_HEADER
#define LFC_ARRAY_HEADER

#include <stdlib.h>

#include "lfc/utils/optional.h"

// Fixed-size, checked array
typedef struct {
    void* data;
    size_t len;
} array_t;

// Initialize a new, empty array
void array_new(array_t* array);

// Initialize the array with the given contents
void array_init(array_t* array, void* data, size_t len);

// Retrieve the value at the given index in the array
// Panics if the index is out of bounds
void* array_get(array_t* array, size_t index);

// Set the value at the given index array
// Panics if the index is out of bounds
void array_set(array_t* array, size_t index, void* value);

// Search the array for the given element
// Returns the appropriate index if it exists, otherwise null
option_t array_find(array_t* array, void* elem);

#endif
