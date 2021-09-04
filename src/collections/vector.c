#include "lfc/collections/vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lfc/utils/mem.h"
#include "lfc/utils/panic.h"

void vec_init(vector_t* vec, size_t elem_size, size_t capacity) {
    vec->data = malloc_unwrap(elem_size, capacity, "[vec_init] failed to alloc vector data");
    vec->elem_size = elem_size;
    vec->len = 0;
    vec->capacity = capacity;
}

void vec_new(vector_t* vec, size_t elem_size) {
    vec_init(vec, elem_size, VEC_DEFAULT_CAPACITY);
}

void vec_free(vector_t* vec, free_fn_t elem_free) {
    if (elem_free != NULL) {
        for (size_t i = 0; i < vec->len; i++) {
            void* elem = vec_at(vec, i);
            elem_free(elem);
        }
    }

    free(vec->data);
}

void* vec_at(vector_t* vec, size_t index) {
    if (index >= vec->len) {
        panic(1, "[vec_at] index %li out of bounds for vector of length %li", index, vec->len);
    }

    return vec->data + index * vec->elem_size;
}

uint8_t vec_is_empty(vector_t* vec) {
    return vec->len == 0;
}

void vec_push(vector_t* vec, void* val) {
    if (vec->len == vec->capacity) {
        vec->capacity *= 2;
        vec->data = realloc_unwrap(
            vec->data, vec->elem_size, vec->capacity,
            "[vec_push] unable to expand vector"
        );
    }

    void* elem = vec->data + vec->len * vec->elem_size;
    memcpy(elem, val, vec->elem_size);
    vec->len += 1;
}

void vec_pop(vector_t* vec, void* val) {
    if (vec->len == 0) {
        panic(1, "[vec_pop] can't pop from empty vector");
    }

    void* elem = vec_at(vec, vec->len - 1);
    memcpy(val, elem, vec->elem_size);
    vec->len -= 1;
}
