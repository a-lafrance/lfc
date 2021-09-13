#ifndef LFC_MAP_HEADER
#define LFC_MAP_HEADER

#include <stdint.h>

#include "lfc/collections/array.h"
#include "lfc/utils/hash.h"
#include "lfc/utils/mem.h"

/// A hash map, implemented with separate chaining (like hashset_t); hash and equality functions
/// must be provided for keys. Key-value pairs are stored in an array of linked list-based buckets.
/// Rehashing again occurs when the load factor meets the specified maximum.

// TODO: don't forget to refactor default buckets and max load factor when hash table is implemented.

typedef struct {
    hash_fn_t hash_fn;
    int (*key_eq)(void*, void*);
    array_t buckets;
    size_t size;
} hashmap_t;

// Initialize the hash map with the given properties
void hashmap_init(hashmap_t* map, size_t n_buckets, hash_fn_t hash_fn, int (*key_eq)(void*, void*));

// Free the hash map, cleaning up keys and values appropriately
void hashmap_free(hashmap_t* map, free_fn_t key_free, free_fn_t val_free);

// Retrieve the value for the given key, or null if it doesn't exist
void* hashmap_get(hashmap_t* map, void* key);

// NOTE: change to hashmap_containskey()?
// Determine whether or not a value exists for the given key
uint8_t hashmap_contains(hashmap_t* map, void* key);

// Set the value of the given key; returns whether or not the key exists and frees the value if necessary
uint8_t hashmap_set(hashmap_t* map, void* key, void* value, free_fn_t val_free);

// NOTE: is this necessary?
// Insert the value into the map, without overwriting any pre-existing value; returns whether or not the
// value was inserted
uint8_t hashmap_insert(hashmap_t* map, void* key, void* val);

// Remove the key-value pair for the given key, if it exists, and clean up appropriately
void hashmap_remove(hashmap_t* map, void* key, free_fn_t key_free, free_fn_t val_free);

// Check whether or not the map is empty
uint8_t hashmap_is_empty(hashmap_t* map);

// Return the load factor of the map
double hashmap_load_factor(hashmap_t* map);

// TODO: tree map

#endif
