#include "lfc/collections/map.h"

#include <stdlib.h>

#include "lfc/utils/pair.h"
#include "lfc/utils/panic.h"

// A very limited subset of a linked list to avoid the overhead of list_t
// This is internal to hashmap, so it's implemented here completely and is
// omitted from the header.
struct mapbucket_node {
    struct mapbucket_node* next;
    pair_t data;
};

void mapbucket_node_init(struct mapbucket_node* node, void* key, void* val) {
    node->next = NULL;
    pair_init(&node->data, key, val);
}

void mapbucket_node_free(struct mapbucket_node* node, free_fn_t key_free, free_fn_t val_free) {
    pair_free(&node->data, key_free, val_free);
    free(node);
}


struct mapbucket {
    struct mapbucket_node* head;
};

void mapbucket_init(struct mapbucket* bucket) {
    bucket->head = NULL;
}

void mapbucket_free(struct mapbucket* bucket, free_fn_t key_free, free_fn_t val_free) {
    for (struct mapbucket_node* node = bucket->head; node != NULL; node = node->next) {
        mapbucket_node_free(node, key_free, val_free);
    }
}

void mapbucket_prepend(struct mapbucket* bucket, void* key, void* val) {
    struct mapbucket_node* node = malloc_unwrap(sizeof(struct mapbucket_node), 1, "failed to allocate new map bucket node");
    mapbucket_node_init(node, key, val);

    if (bucket->head != NULL) {
        bucket->head->next = node;
    }

    bucket->head = node;
}

void* mapbucket_pop_first(struct mapbucket* bucket) {
    if (bucket->head == NULL) {
        panic(1, "can't pop from empty mapbucket");
    }

    struct mapbucket_node* node = bucket->head;
    pair_t pair = node->data;

    bucket->head = node->next;
    mapbucket_node_free(node, NULL, NULL);

    return pair.second;
}

void* mapbucket_remove(struct mapbucket* bucket, void* target_key, int (*key_eq)(void*, void*)) {
    struct mapbucket_node* prev = NULL;

    for (struct mapbucket_node* node = bucket->head; node != NULL; node = node->next) {
        void* key = node->data.first;

        if (key_eq(key, target_key)) {
            if (prev != NULL) {
                prev->next = node->next;
            } else {
                bucket->head = node->next;
            }

            pair_t pair = node->data;
            mapbucket_node_free(node, NULL, NULL);

            return pair.second;
        }
    }

    return NULL;
}

uint8_t mapbucket_find(struct mapbucket* bucket, void* target_key, int (*key_eq)(void*, void*)) {
    if (key_eq == NULL) {
        panic(1, "key_eq must not be null");
    }

    for (struct mapbucket_node* node = bucket->head; node != NULL; node = node->next) {
        void* key = node->data.first;

        if (key_eq(key, target_key)) {
            return 1;
        }
    }

    return 0;
}

uint8_t mapbucket_is_empty(struct mapbucket* bucket) {
    return bucket->head == NULL;
}
