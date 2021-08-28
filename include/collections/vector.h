#ifndef LFC_VECTOR_HEADER
#define LFC_VECTOR_HEADER

#include <stdint.h>
#include <stdlib.h>

#include "lfc/utils/mem.h"

#define VEC_DEFAULT_CAPACITY 20

typedef struct {
    void* data;
    size_t elem_size;

    size_t len;
    size_t capacity;
} vector_t;

// NOTE: should vec_expand be public?

void vec_init(vector_t* vec, size_t elem_size, size_t capacity);
void vec_new(vector_t* vec, size_t elem_size);
void vec_free(vector_t* vec, free_fn_t elem_free);
void* vec_at(vector_t* vec, size_t index);
void vec_append(vector_t* vec, void* elem);
void* vec_pop(vector_t* vec);

#endif
