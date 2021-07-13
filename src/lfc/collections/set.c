#include "lfc/collections/set.h"

#include "lfc/collections/array.h"
#include "lfc/collections/linkedlist.h"
#include "lfc/utils/panic.h"

void hashset_init(hashset_t* set, hash_fn_t hash_fn, int (*elem_eq)(void*, void*)) {
    if (hash_fn == NULL) {
        panic(EXIT_FAILURE, "[hashset_t] hash function must be non-null");
    }

    if (elem_eq == NULL) {
        panic(EXIT_FAILURE, "[hashset_t] equality function must be non-null");
    }

    set->hash_fn = hash_fn;
    set->elem_eq = elem_eq;
    set->size = 0;

    array_new(&set->buckets, sizeof(list_t));
}

void hashset_insert(hashset_t* set, void* elem) {
    if (hashset_contains(set, elem)) return;

    // TODO: rehash if necessary

    // get bucket index
    size_t bucket_index = (set->hash_fn)(elem) % set->buckets.len;

    // find bucket
    list_t* bucket = array_get(&set->buckets, bucket_index);

    // insert into bucket
    ll_append(bucket, elem);
    set->size += 1;
}

void hashset_remove(hashset_t* set, void* elem) {
    // get bucket index
    // search bucket for item
    // if found, remove
}

int hashset_contains(hashset_t* set, void* elem) {
    // get bucket index
    // search bucket for item
    // if found, return true; else return false
    return 0;
}

double hashset_load_factor(hashset_t* set) {
    return (double)(set->size) / set->buckets.len;
}
