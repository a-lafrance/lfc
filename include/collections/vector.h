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

void vec_init(vector_t* vec, size_t elem_size, size_t capacity);
void vec_new(vector_t* vec, size_t elem_size);
void vec_free(vector_t* vec, free_fn_t elem_free);

void* vec_at(vector_t* vec, size_t index);
uint8_t vec_is_empty(vector_t* vec);

void vec_push(vector_t* vec, void* val);
void vec_pop(vector_t* vec, void* val);

#endif
