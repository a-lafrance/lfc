#include "lfc/collections/stack.h"

#include "lfc/collections/vector.h"

void stack_init(vstack_t* stack, size_t elem_size) {
    vec_init(&stack->base, elem_size, VEC_DEFAULT_CAPACITY);
}

void stack_free(vstack_t* stack, free_fn_t elem_free) {
    vec_free(&stack->base, elem_free);
}

void stack_push(vstack_t* stack, void* val) {
    vec_push(&stack->base, val);
}

void stack_pop(vstack_t* stack, void* val) {
    vec_pop(&stack->base, val);
}

void* stack_peek(vstack_t* stack) {
    if (stack_is_empty(stack)) {
        return NULL;
    }

    return vec_at(
        &stack->base,
        vec_len(&stack->base) - 1
    );
}

size_t stack_len(vstack_t* stack) {
    return vec_len(&stack->base);
}

uint8_t stack_is_empty(vstack_t* stack) {
    return stack_len(stack) == 0;
}
