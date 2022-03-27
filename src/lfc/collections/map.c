#include "lfc/collections/map.h"

#include <stdint.h>
#include <stdlib.h>

#include "internals/collections/__mapbucket.h"

#include "lfc/collections/array.h"
#include "lfc/collections/set.h"

#include "lfc/utils/pair.h"
#include "lfc/utils/panic.h"


void hashmap_init(hashmap_t* map, size_t n_buckets, hash_fn_t hash_fn, int (*key_eq)(void*, void*)) {
    map->hash_fn = hash_fn;
    map->key_eq = key_eq;
    map->size = 0;

    dynarray_init(&map->buckets, n_buckets, sizeof(struct __mapbucket));

    for (size_t i = 0; i < dynarray_len(&map->buckets); i++) {
        __mapbucket_init(dynarray_at(&map->buckets, i));
    }
}

void hashmap_free(hashmap_t* map, free_fn_t key_free, free_fn_t val_free) {
    for (size_t i = 0; i < dynarray_len(&map->buckets); i++) {
        __mapbucket_free(dynarray_at(&map->buckets, i), key_free, val_free);
    }

    dynarray_free(&map->buckets, NULL);
}

size_t __hashmap_bucket(hashmap_t* map, void* key) {
    return (map->hash_fn)(key) % dynarray_len(&map->buckets);
}

void* hashmap_get(hashmap_t* map, void* key) {
    size_t bucket_index = __hashmap_bucket(map, key);
    struct __mapbucket* bucket = dynarray_at(&map->buckets, bucket_index);

    return __mapbucket_find(bucket, key, map->key_eq);
}

uint8_t hashmap_set(hashmap_t* map, void* target_key, void* new_value, free_fn_t val_free) {
    size_t bucket_index = __hashmap_bucket(map, target_key);
    struct __mapbucket* bucket = dynarray_at(&map->buckets, bucket_index);

    for (struct __mapbucket_node* node = bucket->head; node != NULL; node = node->next) {
        void* key = node->data.first;
        void* value = node->data.second;

        if ((map->key_eq)(key, target_key)) {
            node->data.second = new_value;

            if (val_free != NULL) {
                val_free(value);
            }

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

void __hashmap_rehash(hashmap_t* map) {
    dynarray_t old_buckets = map->buckets;
    hashmap_init(map, dynarray_len(&old_buckets) * 2, map->hash_fn, map->key_eq);

    for (size_t i = 0; i < dynarray_len(&old_buckets); i++) {
        struct __mapbucket* bucket = dynarray_at(&old_buckets, i);

        for (struct __mapbucket_node* node = bucket->head; node != NULL; node = node->next) {
            hashmap_insert(map, node->data.first, node->data.second);
        }

        __mapbucket_free(bucket, NULL, NULL);
    }

    dynarray_free(&old_buckets, NULL);
}

uint8_t hashmap_insert(hashmap_t* map, void* key, void* val) {
    if (!hashmap_contains(map, key)) {
        if (hashmap_load_factor(map) > MAX_LOAD_FACTOR) {
            __hashmap_rehash(map);
        }

        size_t bucket_index = __hashmap_bucket(map, key);
        struct __mapbucket* bucket = dynarray_at(&map->buckets, bucket_index);

        __mapbucket_prepend(bucket, key, val);
        map->size += 1;

        return 1;
    } else {
        return 0;
    }
}

void hashmap_remove(hashmap_t* map, void* key, free_fn_t key_free, free_fn_t val_free) {
    size_t bucket_index = __hashmap_bucket(map, key);
    struct __mapbucket* bucket = dynarray_at(&map->buckets, bucket_index);

    if (__mapbucket_remove(bucket, key, map->key_eq, key_free, val_free)) {
        map->size -= 1;
    }
}

uint8_t hashmap_is_empty(hashmap_t* map) {
    return map->size == 0;
}

double hashmap_load_factor(hashmap_t* map) {
    return (double)map->size / dynarray_len(&map->buckets);
}

size_t hashmap_n_buckets(hashmap_t* map) {
    return dynarray_len(&map->buckets);
}
