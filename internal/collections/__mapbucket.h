#ifndef LFC___mapbucket_HEADER
#define LFC___mapbucket_HEADER

#include "lfc/utils/mem.h"
#include "lfc/utils/pair.h"

/// A very limited subset of a linked list to avoid the overhead of list_t. Its only use is within `hashmap_t`, but
/// it's here anyway as somewhat of a proof of concept for the internal interface

struct __mapbucket_node {
    struct __mapbucket_node* next;
    pair_t data;
};

// Initialize the map bucket node with the given key and value
void __mapbucket_node_init(struct __mapbucket_node* node, void* key, void* val);

// Free the map bucket, and clean up the keys and values appropriately, if necessary
void __mapbucket_node_free(struct __mapbucket_node* node, free_fn_t key_free, free_fn_t val_free);

struct __mapbucket {
    struct __mapbucket_node* head;
};

// Initialize a new empty map bucket
void __mapbucket_init(struct __mapbucket* bucket);

// Free the map bucket, and clean up its keys and values appropriately, if necessary
void __mapbucket_free(struct __mapbucket* bucket, free_fn_t key_free, free_fn_t val_free);

// Prepend the given key-value pair to the map bucket
void __mapbucket_prepend(struct __mapbucket* bucket, void* key, void* val);

// Remove the key-value pair for the given key from the map bucket, cleaning up keys and values as necessary
void __mapbucket_remove(struct __mapbucket* bucket, void* target_key, int (*key_eq)(void*, void*), free_fn_t key_free, free_fn_t val_free);

// Find the value for the given key, if it exists
void* __mapbucket_find(struct __mapbucket* bucket, void* target_key, int (*key_eq)(void*, void*));

// Check whether or not the map bucket is empty
uint8_t __mapbucket_is_empty(struct __mapbucket* bucket);

#endif
