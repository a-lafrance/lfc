#include "lfc/collections/queue.h"

#include "lfc/collections/linkedlist.h"

void queue_init(queue_t* q) {
    ll_init(&q->base);
}

void queue_free(queue_t* q, free_fn_t elem_free) {
    ll_free(&q->base, elem_free);
}

void queue_push(queue_t* q, void* val) {
    ll_append(&q->base, val);
}

void* queue_pop(queue_t* q) {
    return ll_pop_first(&q->base);
}

void* queue_peek(queue_t* q) {
    return ll_last(&q->base);
}

size_t queue_len(queue_t* q) {
    return ll_len(&q->base);
}

uint8_t queue_is_empty(queue_t* q) {
    return queue_len(q) == 0;
}
