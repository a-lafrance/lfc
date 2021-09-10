#include "lfc/collections/map.h"

#include <stdint.h>
#include <stdlib.h>

#include "lfc/collections/array.h"
#include "lfc/utils/pair.h"
#include "lfc/utils/panic.h"

// A very limited subset of a linked list to avoid the overhead of list_t
// This is internal to hashmap, so it's implemented here completely and is
// omitted from the header.
struct __mapbucket_node {
    struct __mapbucket_node* next;
    pair_t data;
};

void __mapbucket_node_init(struct __mapbucket_node* node, void* key, void* val) {
    node->next = NULL;
    pair_init(&node->data, key, val);
}

void __mapbucket_node_free(struct __mapbucket_node* node, free_fn_t key_free, free_fn_t val_free) {
    pair_free(&node->data, key_free, val_free);
    free(node);
}


struct __mapbucket {
    struct __mapbucket_node* head;
};

void mapbucket_init(struct __mapbucket* bucket) {
    bucket->head = NULL;
}

void mapbucket_free(struct __mapbucket* bucket, free_fn_t key_free, free_fn_t val_free) {
    for (struct __mapbucket_node* node = bucket->head; node != NULL; node = node->next) {
        __mapbucket_node_free(node, key_free, val_free);
    }
}

void mapbucket_prepend(struct __mapbucket* bucket, void* key, void* val) {
    struct __mapbucket_node* node = malloc_unwrap(sizeof(struct __mapbucket_node), 1, "failed to allocate new map bucket node");
    __mapbucket_node_init(node, key, val);

    if (bucket->head != NULL) {
        bucket->head->next = node;
    }

    bucket->head = node;
}

void* mapbucket_pop_first(struct __mapbucket* bucket) {
    if (bucket->head == NULL) {
        panic(1, "can't pop from empty __mapbucket");
    }

    struct __mapbucket_node* node = bucket->head;
    pair_t pair = node->data;

    bucket->head = node->next;
    __mapbucket_node_free(node, NULL, NULL);

    return pair.second;
}

void mapbucket_remove(struct __mapbucket* bucket, void* target_key, int (*key_eq)(void*, void*), free_fn_t key_free, free_fn_t val_free) {
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

void* mapbucket_find(struct __mapbucket* bucket, void* target_key, int (*key_eq)(void*, void*)) {
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

uint8_t mapbucket_is_empty(struct __mapbucket* bucket) {
    return bucket->head == NULL;
}


/// --- hashmap_t ---

void hashmap_init(hashmap_t* map, size_t n_buckets, hash_fn_t hash_fn, int (*key_eq)(void*, void*)) {
    map->hash_fn = hash_fn;
    map->key_eq = key_eq;
    map->size = 0;

    struct __mapbucket* buckets = malloc_unwrap(sizeof(struct __mapbucket), n_buckets, "[hashmap_init] failed to alloc buckets");
    array_init(&map->buckets, buckets, n_buckets, sizeof(struct __mapbucket));
}

void hashmap_free(hashmap_t* map, free_fn_t key_free, free_fn_t val_free) {
    for (size_t i = 0; i < map->buckets.len; i++) {
        mapbucket_free(array_at(&map->buckets, i), key_free, val_free);
    }

    array_free(&map->buckets, NULL);
}

size_t hashmap_bucket(hashmap_t* map, void* key) {
    return (map->hash_fn)(key) % map->buckets.len;
}

void* hashmap_get(hashmap_t* map, void* key) {
    size_t bucket_index = hashmap_bucket(map, key);
    struct __mapbucket* bucket = array_at(&map->buckets, bucket_index);

    return mapbucket_find(bucket, key, map->key_eq);
}

void hashmap_set(hashmap_t* map, void* target_key, void* new_value, free_fn_t val_free) {
    size_t bucket_index = hashmap_bucket(map, target_key);
    struct __mapbucket* bucket = array_at(&map->buckets, bucket_index);

    for (struct __mapbucket_node* node = bucket->head; node != NULL; node = node->next) {
        void* key = node->data.first;
        void* value = node->data.second;

        if ((map->key_eq)(key, target_key)) {
            node->data.second = new_value;
            val_free(value);
            return;
        }
    }

    mapbucket_prepend(bucket, target_key, new_value);
}

uint8_t hashmap_contains(hashmap_t* map, void* key) {
    return hashmap_get(map, key) != NULL;
}

uint8_t hashmap_insert(hashmap_t* map, void* key, void* val) {
    if (!hashmap_contains(map, key)) {
        size_t bucket_index = hashmap_bucket(map, key);
        struct __mapbucket* bucket = array_at(&map->buckets, bucket_index);

        mapbucket_prepend(bucket, key, val);
        return 1;
    } else {
        return 0;
    }
}

void hashmap_remove(hashmap_t* map, void* key, free_fn_t key_free, free_fn_t val_free) {
    size_t bucket_index = hashmap_bucket(map, key);
    struct __mapbucket* bucket = array_at(&map->buckets, bucket_index);

    mapbucket_remove(bucket, key, map->key_eq, key_free, val_free);
}

uint8_t hashmap_is_empty(hashmap_t* map) {
    return map->size == 0;
}

double hashmap_load_factor(hashmap_t* map) {
    return (double)map->size / map->buckets.len;
}
