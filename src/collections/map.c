#include "lfc/collections/map.h"

#include <stdint.h>
#include <stdlib.h>

#include "lfc/collections/array.h"
#include "lfc/collections/internal/__mapbucket.h"
#include "lfc/utils/pair.h"
#include "lfc/utils/panic.h"


void hashmap_init(hashmap_t* map, size_t n_buckets, hash_fn_t hash_fn, int (*key_eq)(void*, void*)) {
    map->hash_fn = hash_fn;
    map->key_eq = key_eq;
    map->size = 0;

    struct __mapbucket* buckets = malloc_unwrap(sizeof(struct __mapbucket), n_buckets, "[hashmap_init] failed to alloc buckets");
    array_init(&map->buckets, buckets, n_buckets, sizeof(struct __mapbucket));

    for (size_t i = 0; i < map->buckets.len; i++) {
        __mapbucket_init(array_at(&map->buckets, i));
    }
}

void hashmap_free(hashmap_t* map, free_fn_t key_free, free_fn_t val_free) {
    for (size_t i = 0; i < map->buckets.len; i++) {
        __mapbucket_free(array_at(&map->buckets, i), key_free, val_free);
    }

    array_free(&map->buckets, NULL);
}

size_t hashmap_bucket(hashmap_t* map, void* key) {
    return (map->hash_fn)(key) % map->buckets.len;
}

void* hashmap_get(hashmap_t* map, void* key) {
    size_t bucket_index = hashmap_bucket(map, key);
    struct __mapbucket* bucket = array_at(&map->buckets, bucket_index);

    return __mapbucket_find(bucket, key, map->key_eq);
}

// TODO: rehash

uint8_t hashmap_set(hashmap_t* map, void* target_key, void* new_value, free_fn_t val_free) {
    size_t bucket_index = hashmap_bucket(map, target_key);
    struct __mapbucket* bucket = array_at(&map->buckets, bucket_index);

    for (struct __mapbucket_node* node = bucket->head; node != NULL; node = node->next) {
        void* key = node->data.first;
        void* value = node->data.second;

        if ((map->key_eq)(key, target_key)) {
            node->data.second = new_value;
            val_free(value);

            return 1;
        }
    }

    __mapbucket_prepend(bucket, target_key, new_value);
    map->size += 1;

    return 0;
}

uint8_t hashmap_contains(hashmap_t* map, void* key) {
    return hashmap_get(map, key) != NULL;
}

uint8_t hashmap_insert(hashmap_t* map, void* key, void* val) {
    if (!hashmap_contains(map, key)) {
        size_t bucket_index = hashmap_bucket(map, key);
        struct __mapbucket* bucket = array_at(&map->buckets, bucket_index);

        __mapbucket_prepend(bucket, key, val);
        map->size += 1;

        return 1;
    } else {
        return 0;
    }
}

void hashmap_remove(hashmap_t* map, void* key, free_fn_t key_free, free_fn_t val_free) {
    size_t bucket_index = hashmap_bucket(map, key);
    struct __mapbucket* bucket = array_at(&map->buckets, bucket_index);

    __mapbucket_remove(bucket, key, map->key_eq, key_free, val_free);
}

uint8_t hashmap_is_empty(hashmap_t* map) {
    return map->size == 0;
}

double hashmap_load_factor(hashmap_t* map) {
    return (double)map->size / map->buckets.len;
}
