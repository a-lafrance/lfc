#ifndef LFC_STACK_HEADER
#define LFC_STACK_HEADER

#include <stdint.h>

#include "lfc/collections/vector.h"
#include "lfc/utils/mem.h"

typedef struct {
    vector_t base;
} vstack_t; // "vstack" = "vector stack", which is meant not to conflict with the builtin stack_t

void stack_init(vstack_t* stack, size_t elem_size);
void stack_free(vstack_t* stack, free_fn_t elem_free);

void stack_push(vstack_t* stack, void* val);
void stack_pop(vstack_t* stack, void* val);
void* stack_peek(vstack_t* stack);

size_t stack_len(vstack_t* stack);
uint8_t stack_is_empty(vstack_t* stack);

#endif
