#include "lfc/collections/internal/__mapbucket.h"

#include "lfc/utils/mem.h"
#include "lfc/utils/pair.h"
#include "lfc/utils/panic.h"

void __mapbucket_node_init(struct __mapbucket_node* node, void* key, void* val) {
    node->next = NULL;
    pair_init(&node->data, key, val);
}

void __mapbucket_node_free(struct __mapbucket_node* node, free_fn_t key_free, free_fn_t val_free) {
    pair_free(&node->data, key_free, val_free);
    free(node);
}

void __mapbucket_init(struct __mapbucket* bucket) {
    bucket->head = NULL;
}

void __mapbucket_free(struct __mapbucket* bucket, free_fn_t key_free, free_fn_t val_free) {
    for (struct __mapbucket_node* node = bucket->head; node != NULL; node = node->next) {
        __mapbucket_node_free(node, key_free, val_free);
    }
}

void __mapbucket_prepend(struct __mapbucket* bucket, void* key, void* val) {
    struct __mapbucket_node* node = malloc_unwrap(sizeof(struct __mapbucket_node), 1, "failed to allocate new map bucket node");
    __mapbucket_node_init(node, key, val);

    if (bucket->head != NULL) {
        bucket->head->next = node;
    }

    bucket->head = node;
}

void __mapbucket_remove(struct __mapbucket* bucket, void* target_key, int (*key_eq)(void*, void*), free_fn_t key_free, free_fn_t val_free) {
    struct __mapbucket_node* prev = NULL;

    for (struct __mapbucket_node* node = bucket->head; node != NULL; node = node->next) {
        void* key = node->data.first;

        if (key_eq(key, target_key)) {
            if (prev != NULL) {
                prev->next = node->next;
            } else {
                bucket->head = node->next;
            }

            pair_t pair = node->data;
            __mapbucket_node_free(node, key_free, val_free);
        }
    }
}

void* __mapbucket_find(struct __mapbucket* bucket, void* target_key, int (*key_eq)(void*, void*)) {
    if (key_eq == NULL) {
        panic(1, "key_eq must not be null");
    }

    for (struct __mapbucket_node* node = bucket->head; node != NULL; node = node->next) {
        void* key = node->data.first;
        void* value = node->data.second;

        if (key_eq(key, target_key)) {
            return value;
        }
    }

    return NULL;
}

uint8_t __mapbucket_is_empty(struct __mapbucket* bucket) {
    return bucket->head == NULL;
}
