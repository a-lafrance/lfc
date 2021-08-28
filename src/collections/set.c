#include "lfc/collections/set.h"

#include "lfc/collections/array.h"
#include "lfc/collections/linkedlist.h"

#include "lfc/utils/panic.h"
#include "lfc/utils/mem.h"

array_t hashset_alloc_buckets(size_t n_buckets) {
    list_t* bucket_array = malloc_unwrap(sizeof(list_t), n_buckets, "[hashset_t] failed to alloc buckets");

    array_t buckets;
    array_init(&buckets, bucket_array, n_buckets, sizeof(list_t));

    for (size_t i = 0; i < n_buckets; i++) {
        list_t* bucket = array_at(&buckets, i);
        ll_init(bucket);
    }

    return buckets;
}

void hashset_init(hashset_t* set, size_t n_buckets, hash_fn_t hash_fn, int (*elem_eq)(void*, void*)) {
    if (hash_fn == NULL) {
        panic(EXIT_FAILURE, "[hashset_t] hash function must be non-null");
    }

    if (elem_eq == NULL) {
        panic(EXIT_FAILURE, "[hashset_t] equality function must be non-null");
    }

    set->hash_fn = hash_fn;
    set->elem_eq = elem_eq;
    set->size = 0;
    set->buckets = hashset_alloc_buckets(n_buckets);
}

void hashset_free(hashset_t* set, free_fn_t elem_free) {
    for (size_t i = 0; i < set->buckets.len; i++) {
        list_t* bucket = array_at(&set->buckets, i);
        ll_free(bucket, elem_free);
    }

    array_free(&set->buckets, NULL);
}

void hashset_bucket_free(void* bucket) {
    ll_free(bucket, NULL);
}

void hashset_rehash(hashset_t* set) {
    // make new buckets
    array_t old_buckets = set->buckets;
    set->buckets = hashset_alloc_buckets(set->buckets.len * 2);
    set->size = 0;

    // stick everything from old buckets to new
    for (size_t i = 0; i < old_buckets.len; i++) {
        list_t* bucket = array_at(&old_buckets, i);

        while (!ll_is_empty(bucket)) {
            void* elem = ll_pop_first(bucket);
            hashset_insert(set, elem);
        }
    }

    // free old buckets
    array_free(&old_buckets, &hashset_bucket_free);
}

size_t hashset_bucket_index(hashset_t* set, void* elem) {
    return (set->hash_fn)(elem) % set->buckets.len;
}

void hashset_insert(hashset_t* set, void* elem) {
    if (hashset_contains(set, elem)) return;

    if (hashset_load_factor(set) >= MAX_LOAD_FACTOR) {
        hashset_rehash(set);
    }

    // get bucket index
    size_t bucket_index = hashset_bucket_index(set, elem);

    // find bucket
    list_t* bucket = array_at(&set->buckets, bucket_index);

    // insert into bucket
    ll_append(bucket, elem);
    set->size += 1;
}

void hashset_remove(hashset_t* set, void* elem, free_fn_t elem_free) {
    size_t bucket_index = hashset_bucket_index(set, elem);
    list_t* bucket = array_at(&set->buckets, bucket_index);

    void* removed = ll_remove(bucket, elem, set->elem_eq);

    if (removed != NULL) {
        set->size -= 1;

        if (elem_free != NULL) {
            elem_free(removed);
        }
    }
}

int hashset_contains(hashset_t* set, void* elem) {
    size_t bucket_index = hashset_bucket_index(set, elem);
    list_t* bucket = array_at(&set->buckets, bucket_index);

    return ll_find(bucket, elem, set->elem_eq);
}

int hashset_is_empty(hashset_t* set) {
    return set->size == 0;
}

double hashset_load_factor(hashset_t* set) {
    return (double)(set->size) / set->buckets.len;
}
