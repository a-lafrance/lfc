#ifndef LFC_VECTOR_HEADER
#define LFC_VECTOR_HEADER

#include <stdint.h>
#include <stdlib.h>

#include "lfc/utils/mem.h"

#define VEC_DEFAULT_CAPACITY 20

/// A vector, more or less an "array list" -- a growable, ordered, linear collection.
/// The vector implicitly allocates, and manages memory as long as the free function
/// is called when the vector will go out of scope. Mutation is only supported at the tail (for now),
/// because anything else would constitute an O(n) operation (although support may be added for that later).

typedef struct {
    void* data;
    size_t elem_size;

    size_t len;
    size_t capacity;
} vector_t;

// Initialize a new vector of elements of the given size, with the given capacity.
void vec_init(vector_t* vec, size_t elem_size, size_t capacity);

// Initialize a new vector of elements of the given size, with the default capacity.
void vec_new(vector_t* vec, size_t elem_size);

// Free the vector, and its elements with the provided cleanup function.
void vec_free(vector_t* vec, free_fn_t elem_free);

// Retrieve the specified element in the vector, or panic if the index is out of bounds.
void* vec_at(vector_t* vec, size_t index);

// Check whether or not the vector is empty.
uint8_t vec_is_empty(vector_t* vec);

// Push the value onto the end of the vector. This operation is O(1) amortized over the cost of
// many pushes, because most will be O(1), but every so often a push will be O(n) because of the
// cost of expanding the vector's contents.
void vec_push(vector_t* vec, void* val);

// Pop the value from the end of the vector, or panic if the vector is empty. The vector never
// deallocates on pop.
void vec_pop(vector_t* vec, void* val);

#endif
