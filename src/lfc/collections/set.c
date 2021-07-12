#include "lfc/collections/set.h"

#include "lfc/collections/array.h"
#include "lfc/collections/linkedlist.h"

void hash_set_init(hash_set* set, hash_fn_t hash_fn, int (*elem_eq)(void*, void*)) {
    if (hash_fn == NULL) {
        panic("[hash_set_t] hash function must be non-null");
    }

    if (elem_eq == NULL) {
        panic("[hash_set_t] equality function must be non-null");
    }

    set->hash_fn = hash_fn;
    set->elem_eq = elem_eq;

    array_new(set->buckets, sizeof(list_t));
}

void hash_set_insert(hash_set_t* set, void* elem) {
    // TODO: rehash if necessary

    // get bucket index
    size_t bucket_index = /* hash value */ % /* n buckets */;
    // find bucket
    // insert into bucket
}

void hash_set_remove(hash_set_t* set, void* elem) { // comparator? error if not found?
    // get bucket index
    // search bucket for item
    // if found, remove
}

int hash_set_contains(hash_set_t* set, void* elem) {
    // get bucket index
    // search bucket for item
    // if found, return true; else return false
    return 0;
}
