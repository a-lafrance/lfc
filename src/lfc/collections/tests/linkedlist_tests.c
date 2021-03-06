#include <stdio.h>

#include "lfc/collections/linkedlist.h"
#include "lfc/utils/mem.h"

#include "tests/assert.h"
#include "tests/setup.h"
#include "tests/utils.h"

void assert_list_is_empty(list_t* list) {
    assert_eq(list->head, NULL);
    assert_eq(list->tail, NULL);
    assert_eq(list->len, 0);
}

void assert_list_not_empty(list_t* list, size_t exp_len) {
    assert_ne(list->head, NULL);
    assert_ne(list->tail, NULL);
    assert_eq(list->len, exp_len);
}

void test_ll_init_and_freed_correctly() {
    start_test();

    list_t list;
    ll_init(&list);

    assert_list_is_empty(&list);

    ll_free(&list, NULL);

    end_test();
}

void test_append_and_free_single_value_no_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    int value = 0;
    ll_append(&list, &value);
    assert_list_not_empty(&list, 1);

    int* first = ll_first(&list);
    assert_eq(*first, value);

    ll_free(&list, NULL);

    end_test();
}

void test_append_and_free_single_value_with_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    struct something thing;
    something_init(&thing, 5);

    ll_append(&list, &thing);
    assert_list_not_empty(&list, 1);

    struct something* first = ll_first(&list);
    assert_eq(*first->n, *thing.n);

    ll_free(&list, (free_fn_t)&something_free);

    end_test();
}

void test_append_and_free_many_values_no_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    size_t len = 5;
    int* values = malloc_unwrap(sizeof(int), len, "[linkedlist_tests] unable to alloc value buffer");

    for (size_t i = 0; i < len; i++) {
		values[i] = i;
        ll_append(&list, values + i);
    }

    assert_list_not_empty(&list, len);

    size_t i = 0;

    for (struct __ll_node* node = list.head; node != NULL; node = node->next) {
        int* value = node->data;
        assert_eq(*value, values[i]);

        i++;
    }

    ll_free(&list, NULL);
	free(values);

    end_test();
}

void test_append_and_free_many_values_with_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    size_t len = 5;
    struct something* values = malloc_unwrap(sizeof(struct something), len, "[linkedlist_tests] unable to alloc value buffer");

    for (int i = 0; i < len; i++) {
        something_init(values + i, i);
        ll_append(&list, values + i);
    }

    assert_list_not_empty(&list, len);

    int i = 0;

    for (struct __ll_node* node = list.head; node != NULL; node = node->next) {
        struct something* value = node->data;
        assert_eq(*value->n, *values[i].n);

        i++;
    }

    ll_free(&list, (free_fn_t)&something_free);
	free(values);

    end_test();
}

void test_prepend_and_free_single_value_no_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    int value = 0;
    ll_prepend(&list, &value);
    assert_list_not_empty(&list, 1);

    int* first = ll_first(&list);
    assert_eq(*first, value);

    ll_free(&list, NULL);

    end_test();
}

void test_prepend_and_free_single_value_with_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    struct something thing;
    something_init(&thing, 5);

    ll_prepend(&list, &thing);
    assert_list_not_empty(&list, 1);

    struct something* first = ll_first(&list);
    assert_eq(*first->n, *thing.n);

    ll_free(&list, (free_fn_t)&something_free);

    end_test();
}

void test_prepend_and_free_many_values_no_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    size_t len = 5;
	int* values = malloc_unwrap(sizeof(int), len, "[linkedlist_tests] failed to alloc value buffer");

    for (size_t i = 0; i < len; i++) {
		values[i] = i;
        ll_prepend(&list, values + i);
    }

    assert_list_not_empty(&list, len);

    size_t i = len - 1;

    for (struct __ll_node* node = list.head; node != NULL; node = node->next) {
        int* value = node->data;
        assert_eq(*value, values[i]);

        i--;
    }

    ll_free(&list, NULL);
	free(values);

    end_test();
}

void test_prepend_and_free_many_values_with_cleanup() {
    start_test();

    list_t list;
    ll_init(&list);

    size_t len = 5;
    struct something* values = malloc_unwrap(sizeof(struct something), len, "[linkedlist_tests] unable to alloc value buffer");

    for (int i = 0; i < len; i++) {
        something_init(values + i, i);
        ll_prepend(&list, values + i);
    }

    assert_list_not_empty(&list, len);

    int i = len - 1;

    for (struct __ll_node* node = list.head; node != NULL; node = node->next) {
        struct something* value = node->data;
        assert_eq(*value->n, *values[i].n);

        i--;
    }

    ll_free(&list, (free_fn_t)&something_free);
	free(values);

    end_test();
}

void test_front_pop_from_empty_list() {
    start_test();

    list_t list;
    ll_init(&list);

    assert_eq(ll_pop_first(&list), NULL);
    assert_list_is_empty(&list);

    ll_free(&list, NULL);

    end_test();
}

void test_front_pop_from_single_element() {
    start_test();

    list_t list;
    ll_init(&list);

    int value = 0;
    ll_append(&list, &value);

    assert_eq(*(int*)ll_pop_first(&list), value);
    assert_list_is_empty(&list);

    ll_free(&list, NULL);

    end_test();
}

void test_front_pop_from_many_elements() {
    start_test();

    list_t list;
    ll_init(&list);

    int len = 5;
	int* values = malloc_unwrap(sizeof(int), len, "[linkedlist_tests] failed to alloc value buffer");

    for (int i = 0; i < len; i++) {
		values[i] = i;
        ll_prepend(&list, values + i);
    }

    assert_eq(*(int*)ll_pop_first(&list), values[len - 1]);
    assert_list_not_empty(&list, len - 1);

    ll_free(&list, NULL);
	free(values);

    end_test();
}

void test_find_in_empty_list() {
    start_test();

    list_t list;
    ll_init(&list);

    int target = 5;
    assert_eq(ll_find(&list, &target, &int_eq), 0);

    ll_free(&list, NULL);

    end_test();
}

void test_find_when_present() {
    start_test();

    list_t list;
    ll_init(&list);

    int len = 5;
	int* values = malloc_unwrap(sizeof(int), len, "[linkedlist_tests] failed to alloc value buffer");

    for (int i = 0; i < len; i++) {
		values[i] = i;
        ll_append(&list, values + i);
    }

    int target = len / 2;
    assert_eq(ll_find(&list, &target, &int_eq), 1);

    ll_free(&list, NULL);
	free(values);

    end_test();
}

void test_find_when_not_present() {
    start_test();

    list_t list;
    ll_init(&list);

    int len = 5;
    int* values = malloc_unwrap(sizeof(int), len, "[linkedlist_tests] failed to alloc value buffer");

    for (int i = 0; i < len; i++) {
		values[i] = i;
        ll_append(&list, values + i);
    }

    assert_eq(ll_find(&list, &len, &int_eq), 0);

    ll_free(&list, NULL);
	free(values);

    end_test();
}

void test_remove_in_empty_list() {
    start_test();

    list_t list;
    ll_init(&list);

    int target = 5;
    assert_eq(ll_remove(&list, &target, &int_eq), NULL);
    assert_list_is_empty(&list);

    ll_free(&list, NULL);

    end_test();
}

void test_remove_when_present() {
    start_test();

    list_t list;
    ll_init(&list);

    int len = 5;
    int* values = malloc_unwrap(sizeof(int), len, "[linkedlist_tests] failed to alloc value buffer");

    for (int i = 0; i < len; i++) {
		values[i] = i;
        ll_append(&list, values + i);
    }

    int target = len / 2;
    int* removed = ll_remove(&list, &target, &int_eq);

    assert_ne(removed, NULL);
    assert_eq(*removed, target);
    assert_list_not_empty(&list, len - 1);

    ll_free(&list, NULL);
	free(values);

    end_test();
}

void test_remove_when_not_present() {
    start_test();

    list_t list;
    ll_init(&list);

    int len = 5;
    int* values = malloc_unwrap(sizeof(int), len, "[linkedlist_tests] failed to alloc value buffer");

    for (int i = 0; i < len; i++) {
		values[i] = i;
        ll_append(&list, values + i);
    }

    assert_eq(ll_remove(&list, &len, &int_eq), NULL);
    assert_list_not_empty(&list, len);

    ll_free(&list, NULL);
	free(values);

    end_test();
}

void test_remove_creating_empty_list() {
    start_test();

    list_t list;
    ll_init(&list);

    int value = 0;
    ll_append(&list, &value);

    int* removed = ll_remove(&list, &value, &int_eq);

    assert_ne(removed, NULL);
    assert_eq(value, *removed);
    assert_list_is_empty(&list);

    ll_free(&list, NULL);

    end_test();
}

void test_empty_list_is_empty() {
    start_test();

    list_t list;
    ll_init(&list);
    assert(ll_is_empty(&list));

    ll_free(&list, NULL);

    end_test();
}

void test_one_elem_list_not_empty() {
    start_test();

    list_t list;
    ll_init(&list);

    int value = 0;
    ll_append(&list, &value);
    assert_false(ll_is_empty(&list));

    ll_free(&list, NULL);

    end_test();
}

void test_many_elem_list_not_empty() {
    start_test();

    list_t list;
    ll_init(&list);

    int len = 5;
    int* values = malloc_unwrap(sizeof(int), len, "[linkedlist_tests] failed to alloc value buffer");

    for (int i = 0; i < len; i++) {
		values[i] = i;
        ll_append(&list, values + i);
    }

    assert_false(ll_is_empty(&list));

    ll_free(&list, NULL);
	free(values);

    end_test();
}


void run_linkedlist_tests() {
    start_suite();

    test_ll_init_and_freed_correctly();

    test_append_and_free_single_value_no_cleanup();
    test_append_and_free_single_value_with_cleanup();
    test_append_and_free_many_values_no_cleanup();
    test_append_and_free_many_values_with_cleanup();

    test_prepend_and_free_single_value_no_cleanup();
    test_prepend_and_free_single_value_with_cleanup();
    test_prepend_and_free_many_values_no_cleanup();
    test_prepend_and_free_many_values_with_cleanup();

    test_front_pop_from_empty_list();
    test_front_pop_from_single_element();
    test_front_pop_from_many_elements();

    test_find_in_empty_list();
    test_find_when_present();
    test_find_when_not_present();

    test_remove_in_empty_list();
    test_remove_when_present();
    test_remove_when_not_present();
    test_remove_creating_empty_list();

    test_empty_list_is_empty();
    test_one_elem_list_not_empty();
    test_many_elem_list_not_empty();

    end_suite();
}
