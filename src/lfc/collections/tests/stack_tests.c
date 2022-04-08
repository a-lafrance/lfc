#include "lfc/collections/stack.h"

#include "tests/assert.h"
#include "tests/setup.h"
#include "tests/utils.h"

void test_stack_init_correctly() {
    start_test();

    vstack_t stack;
    stack_init(&stack, sizeof(int));

    assert_eq(stack_len(&stack), 0);
    assert_eq(stack_peek(&stack), NULL);
    assert(stack_is_empty(&stack));

    stack_free(&stack, NULL);

    end_test();
}

void test_stack_push_pop_on_empty() {
    start_test();

    int i = 5;
    vstack_t stack;
    stack_init(&stack, sizeof(int));
    stack_push(&stack, &i);

    assert_eq(stack_len(&stack), 1);
    assert_eq(*(int*)stack_peek(&stack), i);
    assert_false(stack_is_empty(&stack));

    int n;
    stack_pop(&stack, &n);

    assert_eq(n, i);
    assert_eq(stack_len(&stack), 0);
    assert_eq(stack_peek(&stack), NULL);
    assert(stack_is_empty(&stack));

    stack_free(&stack, NULL);

    end_test();
}

void test_stack_push_pop_many() {
    start_test();

    int len = 3;
    int v[] = {8, 15, 17};
    vstack_t stack;
    stack_init(&stack, sizeof(int));

    for (unsigned int i = 0; i < len; i++) {
        stack_push(&stack, v + i);

        assert_eq(stack_len(&stack), i + 1);
        assert_eq(*(int*)stack_peek(&stack), v[i]);
        assert_false(stack_is_empty(&stack));
    }

    assert_eq(stack_len(&stack), len);
    assert_eq(*(int*)stack_peek(&stack), v[len - 1]);
    assert_false(stack_is_empty(&stack));

    for (int i = len - 1; i >= 0; i--) {
        int n;
        stack_pop(&stack, &n);

        assert_eq(n, v[i]);
        assert_eq(stack_len(&stack), i);

        if (i > 0) {
            assert_eq(*(int*)stack_peek(&stack), v[i - 1]);
        } else {
            assert_eq(stack_peek(&stack), NULL);
        }

        assert_eq(stack_is_empty(&stack), i == 0);
    }

    stack_free(&stack, NULL);

    end_test();
}

void run_stack_tests() {
    start_suite();

    test_stack_init_correctly();
    test_stack_push_pop_on_empty();
    test_stack_push_pop_many();

    end_suite();
}
