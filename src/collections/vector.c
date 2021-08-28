#include "lfc/collections/vector.h"

#include <stdlib.h>

#include "lfc/utils/mem.h"

void vec_init(vector_t* vec, size_t elem_size, size_t capacity) {
    vec->data = malloc_unwrap(elem_size, capacity, "[vector_t] failed to alloc vector data");
    vec->elem_size = elem_size;
    vec->len = 0;
    vec->capacity = capacity;
}

void vec_new(vector_t* vec, size_t elem_size) {
    vec_init(vec, elem_size, VEC_DEFAULT_CAPACITY);
}

void vec_free(vector_t* vec, free_fn_t elem_free) {
    // free dyn data
    // call elem free on each one
}

void* vec_at(vector_t* vec, size_t index) {
    // get the pointer
    return NULL;
}

void vec_append(vector_t* vec, void* elem) {
    // stick the thing at the end, expand if necessary
}

void* vec_pop(vector_t* vec) {
    // pop the first thing off (how to return result?)
    return NULL;
}
