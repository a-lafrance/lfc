#include "lfc/collections/set.h"
#include "lfc/collections/array.h"

void hash_set_init(hash_set* set, hash_fn_t hash_fn) {
    set->hash_fn = hash_fn;
    array_init(set->buckets);
}

void hash_set_insert(hash_set* set, void* elem) {
    // rehash if necessary

    // get bucket index
    // find bucket
    // insert into bucket
}

void hash_set_remove(hash_set* set, void* elem) { // comparator? error if not found?
    // get bucket index
    // search bucket for item
    // if found, remove
}

int hash_set_contains(hash_set* set, void* elem) {
    // get bucket index
    // search bucket for item
    // if found, return true; else return false
    return 0;
}
