#include "setup.h"

#include "lfc/collections/vector.h"
#include "lfc/utils/mem.h"

#include "assert.h"
#include "utils.h"


void test_vec_init_with_capacity_correctly_no_cleanup() {
    start_test();

    vector_t vec;
    size_t capacity = 10;
    vec_init(&vec, sizeof(int), capacity);

    assert_eq(vec.elem_size, sizeof(int));
    assert_eq(vec.len, 0);
    assert_eq(vec.capacity, capacity);
    assert(vec_is_empty(&vec));

    vec_free(&vec, NULL);

    end_test();
}

void test_vec_init_with_capacity_correctly_with_cleanup() {
    start_test();

    vector_t vec;
    size_t capacity = 10;
    vec_init(&vec, sizeof(struct something), capacity);

    assert_eq(vec.elem_size, sizeof(struct something));
    assert_eq(vec.len, 0);
    assert_eq(vec.capacity, capacity);
    assert(vec_is_empty(&vec));

    vec_free(&vec, (free_fn_t)&something_free);

    end_test();
}

void test_vec_default_init_correctly_no_cleanup() {
    start_test();

    vector_t vec;
    vec_new(&vec, sizeof(int));

    assert_eq(vec.elem_size, sizeof(int));
    assert_eq(vec.len, 0);
    assert_eq(vec.capacity, VEC_DEFAULT_CAPACITY);
    assert(vec_is_empty(&vec));

    vec_free(&vec, NULL);

    end_test();
}

void test_vec_default_init_correctly_with_cleanup() {
    start_test();

    vector_t vec;
    vec_new(&vec, sizeof(struct something));

    assert_eq(vec.elem_size, sizeof(struct something));
    assert_eq(vec.len, 0);
    assert_eq(vec.capacity, VEC_DEFAULT_CAPACITY);
    assert(vec_is_empty(&vec));

    vec_free(&vec, (free_fn_t)&something_free);

    end_test();
}

void test_vec_value_appended_and_retrieved_correctly_no_cleanup() {
    start_test();

    vector_t vec;
    vec_new(&vec, sizeof(int));

    int n = 3;
    vec_append(&vec, &n);
    assert_eq(vec.len, 1);
    assert_eq(vec.capacity, VEC_DEFAULT_CAPACITY);
    assert_false(vec_is_empty(&vec));

    int* elem = vec_at(&vec, 0);
    assert_eq(*elem, n);

    vec_free(&vec, NULL);

    end_test();
}

void test_vec_value_appended_and_retrieved_correctly_with_cleanup() {
    start_test();

    vector_t vec;
    vec_new(&vec, sizeof(struct something));

    struct something s;
    something_init(&s, 3);
    vec_append(&vec, &s);

    assert_eq(vec.len, 1);
    assert_eq(vec.capacity, VEC_DEFAULT_CAPACITY);
    assert_false(vec_is_empty(&vec));

    struct something* elem = vec_at(&vec, 0);
    assert_eq(*(elem->n), *(s.n));

    vec_free(&vec, (free_fn_t)&something_free);

    end_test();
}

void test_vec_many_values_appended_and_retrieved_correctly_no_cleanup() {
    start_test();

    vector_t vec;
    vec_new(&vec, sizeof(int));

    size_t n = 5;
    int numbers[n];
    for (size_t i = 0; i < n; i++) {
        numbers[i] = i;
        vec_append(&vec, &numbers[i]);

        assert_eq(vec.len, i + 1);
        assert_eq(vec.capacity, VEC_DEFAULT_CAPACITY);
    }

    assert_false(vec_is_empty(&vec));
    for (size_t i = 0; i < n; i++) {
        int* elem = vec_at(&vec, i);
        assert_eq(*elem, numbers[i]);
    }

    vec_free(&vec, NULL);

    end_test();
}

void test_vec_many_values_appended_and_retrieved_correctly_with_cleanup() {
    start_test();

    vector_t vec;
    vec_new(&vec, sizeof(struct something));

    size_t n = 5;
    struct something s[n];
    for (size_t i = 0; i < n; i++) {
        something_init(&s[i], i);
        vec_append(&vec, &s[i]);

        assert_eq(vec.len, i + 1);
        assert_eq(vec.capacity, VEC_DEFAULT_CAPACITY);
    }

    assert_false(vec_is_empty(&vec));
    for (size_t i = 0; i < n; i++) {
        struct something* elem = vec_at(&vec, i);
        assert_eq(*(elem->n), *(s[i].n));
    }

    vec_free(&vec, (free_fn_t)&something_free);

    end_test();
}

void test_vec_values_appended_and_expanded_correctly_no_cleanup() {
    start_test();

    vector_t vec;
    vec_new(&vec, sizeof(int));

    int n = VEC_DEFAULT_CAPACITY + 1;
    int numbers[n];
    for (size_t i = 0; i < n; i++) {
        numbers[i] = i;
        vec_append(&vec, &numbers[i]);

        assert_eq(vec.len, i + 1);
        assert_eq(vec.capacity, i == n - 1 ? 2 * VEC_DEFAULT_CAPACITY : VEC_DEFAULT_CAPACITY);
    }

    assert_false(vec_is_empty(&vec));
    for (size_t i = 0; i < n; i++) {
        int* elem = vec_at(&vec, i);
        assert_eq(*elem, numbers[i]);
    }

    vec_free(&vec, NULL);

    end_test();
}

void test_vec_values_appended_and_expanded_correctly_with_cleanup() {
    start_test();

    vector_t vec;
    vec_new(&vec, sizeof(struct something));

    int n = VEC_DEFAULT_CAPACITY + 1;
    struct something items[n];
    for (size_t i = 0; i < n; i++) {
        something_init(items + i, i);
        vec_append(&vec, items + i);

        assert_eq(vec.len, i + 1);
        assert_eq(vec.capacity, i == n - 1 ? 2 * VEC_DEFAULT_CAPACITY : VEC_DEFAULT_CAPACITY);
    }

    assert_false(vec_is_empty(&vec));
    for (size_t i = 0; i < n; i++) {
        struct something* elem = vec_at(&vec, i);
        assert_eq(*(elem->n), *(items[i].n));
    }

    vec_free(&vec, (free_fn_t)&something_free);

    end_test();
}

void test_vec_pop_from_one_elem_makes_empty() {
    start_test();

    vector_t vec;
    vec_new(&vec, sizeof(int));

    int n = 3;
    vec_append(&vec, &n);

    int popped;
    vec_pop(&vec, &popped);
    assert_eq(popped, n);
    assert(vec_is_empty(&vec));

    vec_free(&vec, NULL);

    end_test();
}

void test_vec_pop_from_many_elems_shortens_correctly() {
    start_test();

    vector_t vec;
    vec_new(&vec, sizeof(int));

    size_t n = 5;
    int numbers[n];
    for (size_t i = 0; i < n; i++) {
        numbers[i] = i;
        vec_append(&vec, &numbers[i]);
    }

    int popped;
    vec_pop(&vec, &popped);
    assert_eq(popped, n - 1);
    assert_false(vec_is_empty(&vec));

    vec_free(&vec, NULL);

    end_test();
}

void run_vector_tests() {
    start_suite();

    test_vec_init_with_capacity_correctly_no_cleanup();
    test_vec_init_with_capacity_correctly_with_cleanup();
    test_vec_default_init_correctly_no_cleanup();
    test_vec_default_init_correctly_with_cleanup();

    test_vec_value_appended_and_retrieved_correctly_no_cleanup();
    test_vec_value_appended_and_retrieved_correctly_with_cleanup();
    test_vec_many_values_appended_and_retrieved_correctly_no_cleanup();
    test_vec_many_values_appended_and_retrieved_correctly_with_cleanup();
    test_vec_values_appended_and_expanded_correctly_no_cleanup();
    test_vec_values_appended_and_expanded_correctly_with_cleanup();

    test_vec_pop_from_one_elem_makes_empty();
    test_vec_pop_from_many_elems_shortens_correctly();

    end_suite();
}
