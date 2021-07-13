#ifndef LFC_VECTOR_HEADER
#define LFC_VECTOR_HEADER

#include <stdlib.h>

typedef struct {
    void* data;
    size_t elem_size;
    size_t len;
    size_t capacity;
} vec_t;

// Initialize a new vector from the given sized pointer
// The vector is initialized with capacity equal to the length of the initial array
// NOTE: the given pointer must be dynamically allocated -- if not, undefined behavior can occur
void vec_init(vec_t* vector, void* data, size_t len, size_t elem_size);

// Free the contents of the given vector
// Note that this function by default frees each element pointer, so the provided function must only free the contents of each element
//   not the pointer itself. (Although by convention maybe it shouldn't do that idk)
void vec_free(vec_t* vector, void (*elem_free)(void*));

// Initialize a new empty vector with the given capacity
void vec_new(void* vector, size_t elem_size, size_t capacity);

// Retrieve a pointer to the element at the given index in the vector
void* vec_get(void* vector, size_t index);

// Set the value of the element at the given index in the vector
// Returns a pointer to the old value, in case it must be freed
void* vec_set(void* vector, size_t index, void* data);

// Appends the element to the end of the vector, growing the size of the vector if needed
void vec_append(void* vector, void* data);

// Pop the last element from the end of the vector, and return it
void* vec_pop(void* vector);

#endif
