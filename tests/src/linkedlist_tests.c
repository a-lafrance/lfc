#include "linkedlist_tests.h"

#include "assert.h"
#include "setup.h"
#include "utils.h"

#include "lfc/collections/linkedlist.h"
#include "lfc/utils/mem.h"

#include <stdio.h>

void test_ll_init_and_freed_correctly() {
    start_test();

    list_t list;
    ll_init(&list);

    assert_eq(list.head, NULL);
    assert_eq(list.tail, NULL);
    assert_eq(list.len, 0);

    ll_free(&list, NULL);

    end_test();
}

void test_append_and_free_single_value_no_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    int* value = calloc_unwrap(sizeof(int), 1, "[linkedlist_tests] unable to alloc int value");
    ll_append(&list, value);

    assert_ne(list.head, NULL);
    assert_ne(list.tail, NULL);
    assert_eq(list.len, 1);

    int* first = ll_first(&list);
    assert_eq(*first, 0);

    ll_free(&list, NULL);

    end_test();
}

void test_append_and_free_single_value_with_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    struct something* thing = malloc_unwrap(sizeof(struct something), 1, "[linkedlist_tests] failed to alloc struct value");
    something_init(thing, 5);
    ll_append(&list, thing);

    assert_ne(list.head, NULL);
    assert_ne(list.tail, NULL);
    assert_eq(list.len, 1);

    struct something* first = ll_first(&list);
    assert_eq(*first->n, *thing->n);

    ll_free(&list, &something_free);

    end_test();
}

void test_append_and_free_many_values_no_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    size_t len = 5;

    for (size_t i = 0; i < len; i++) {
        int* value = malloc_unwrap(sizeof(int), 1, "[linkedlist_tests] unable to alloc int value");
        *value = i;

        ll_append(&list, value);
    }

    assert_ne(list.head, NULL);
    assert_ne(list.tail, NULL);
    assert_eq(list.len, len);

    int* first = ll_first(&list);
    assert_eq(*first, 0);

    ll_free(&list, NULL);

    end_test();
}

void test_append_and_free_many_values_with_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    struct something* thing = malloc_unwrap(sizeof(struct something), 1, "[linkedlist_tests] failed to alloc struct value");
    something_init(thing, 5);
    ll_append(&list, thing);

    assert_ne(list.head, NULL);
    assert_ne(list.tail, NULL);
    assert_eq(list.len, 1);

    struct something* first = ll_first(&list);
    assert_eq(*first->n, *thing->n);

    ll_free(&list, &something_free);

    end_test();
}

// prepend: element correctly prepended
    // to empty list
        // without cleanup
        // with cleanup
    // to non-empty list
        // without cleanup
        // with cleanup
// front pop: element correctly popped
    // to one-element list
    // to empty list
    // to many-element list
// find:
    // non-empty list containing target
    // non-empty list not containing target
    // empty list
// remove:
    // non-empty list containing target
    // non-empty list not containing target
    // empty list
// empty:
    // empty list
    // one element list
    // many element list

void run_linkedlist_tests() {
    start_suite();

    test_ll_init_and_freed_correctly();

    test_append_and_free_single_value_no_cleanup();
    test_append_and_free_single_value_with_cleanup();

    end_suite();
}
