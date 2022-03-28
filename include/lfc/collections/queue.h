#ifndef LFC_QUEUE_HEADER
#define LFC_QUEUE_HEADER

#include <stdint.h>

#include "lfc/collections/linkedlist.h"
#include "lfc/utils/mem.h"

typedef struct {
    list_t base;
} queue_t;

void queue_init(queue_t* q);
void queue_free(queue_t* q, free_fn_t elem_free);

void queue_push(queue_t* q, void* val);
void* queue_pop(queue_t* q);
void* queue_peek(queue_t* q);

size_t queue_len(queue_t* q);
uint8_t queue_is_empty(queue_t* q);

#endif
