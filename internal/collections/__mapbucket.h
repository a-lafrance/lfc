#ifndef LFC_MAPBUCKET_HEADER
#define LFC_MAPBUCKET_HEADER

#include "lfc/utils/mem.h"
#include "lfc/utils/pair.h"

/// A very limited subset of a linked list to avoid the overhead of list_t
/// This is internal to hashmap, so it's implemented here completely and is
/// omitted from the header.

struct __mapbucket_node {
    struct __mapbucket_node* next;
    pair_t data;
};

void __mapbucket_node_init(struct __mapbucket_node* node, void* key, void* val);
void __mapbucket_node_free(struct __mapbucket_node* node, free_fn_t key_free, free_fn_t val_free);

struct __mapbucket {
    struct __mapbucket_node* head;
};

void __mapbucket_init(struct __mapbucket* bucket);
void __mapbucket_free(struct __mapbucket* bucket, free_fn_t key_free, free_fn_t val_free);
void __mapbucket_prepend(struct __mapbucket* bucket, void* key, void* val);
void* __mapbucket_pop_first(struct __mapbucket* bucket);
void __mapbucket_remove(struct __mapbucket* bucket, void* target_key, int (*key_eq)(void*, void*), free_fn_t key_free, free_fn_t val_free);
void* __mapbucket_find(struct __mapbucket* bucket, void* target_key, int (*key_eq)(void*, void*));
uint8_t __mapbucket_is_empty(struct __mapbucket* bucket);

#endif
