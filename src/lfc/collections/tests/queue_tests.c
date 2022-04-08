#include "lfc/collections/queue.h"

#include "tests/assert.h"
#include "tests/setup.h"
#include "tests/utils.h"

void test_queue_init_correctly() {
    start_test();

    queue_t q;
    queue_init(&q);

    assert_eq(queue_len(&q), 0);
    assert_eq(queue_peek(&q), NULL);
    assert(queue_is_empty(&q));

    queue_free(&q, NULL);

    end_test();
}

void test_queue_push_pop_on_empty() {
    start_test();

    int i = 5;
    queue_t q;
    queue_init(&q);
    queue_push(&q, &i);

    assert_eq(queue_len(&q), 1);
    assert_eq(*(int*)queue_peek(&q), i);
    assert_false(queue_is_empty(&q));

    assert_eq(*(int*)queue_pop(&q), i);
    assert_eq(queue_len(&q), 0);
    assert_eq(queue_peek(&q), NULL);
    assert(queue_is_empty(&q));

    queue_free(&q, NULL);

    end_test();
}

void test_queue_push_pop_many() {
    start_test();

    int len = 3;
    int v[] = {8, 15, 17};
    queue_t q;
    queue_init(&q);

    for (unsigned int i = 0; i < len; i++) {
        queue_push(&q, v + i);

        assert_eq(queue_len(&q), i + 1);
        assert_eq(*(int*)queue_peek(&q), v[0]);
        assert_false(queue_is_empty(&q));
    }

    assert_eq(queue_len(&q), len);
    assert_eq(*(int*)queue_peek(&q), v[0]);
    assert_false(queue_is_empty(&q));

    for (int i = 0; i < len; i++) {
        assert_eq(*(int*)queue_pop(&q), v[i]);
        assert_eq(queue_len(&q), len - 1 - i);

        if (i < len - 1) {
            assert_eq(*(int*)queue_peek(&q), v[i + 1]);
        } else {
            assert_eq(queue_peek(&q), NULL);
        }

        assert_eq(queue_is_empty(&q), i == len - 1);
    }

    queue_free(&q, NULL);

    end_test();
}

void run_queue_tests() {
    start_suite();

    test_queue_init_correctly();
    test_queue_push_pop_on_empty();
    test_queue_push_pop_many();

    end_suite();
}
