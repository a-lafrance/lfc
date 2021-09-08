#ifndef LFC_MAP_HEADER
#define LFC_MAP_HEADER

#include <stdint.h>

#include "lfc/collections/array.h"
#include "lfc/utils/hash.h"
#include "lfc/utils/mem.h"

typedef struct {
    hash_fn_t hash_fn;
    int (*key_eq)(void*, void*);
    array_t buckets;
    size_t size;
} hashmap_t;

void hashmap_init(hashmap_t* map, size_t n_buckets, hash_fn_t hash_fn, int (*key_eq)(void*, void*));
void hashmap_free(hashmap_t* map, free_fn_t key_free, free_fn_t val_free);

void* hashmap_get(hashmap_t* map, void* key);
uint8_t hashmap_contains(hashmap_t* map, void* key);

void hashmap_set(hashmap_t* map, void* key, void* value, free_fn_t val_free);
uint8_t hashmap_insert(hashmap_t* map, void* key, void* val);
void hashmap_remove(hashmap_t* map, void* key, free_fn_t key_free, free_fn_t val_free);

uint8_t hashmap_is_empty(hashmap_t* map);
double hashmap_load_factor(hashmap_t* map);

// TODO: tree map

#endif
