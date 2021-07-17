#ifndef LFC_ASSERT_HEADER
#define LFC_ASSERT_HEADER

#include "lfc/utils/panic.h"
#include <stdio.h>

#define assert_or(condition, msg)                  \
if (!(condition)) {                                \
    panic(1, "assertion failed: %s", msg);         \
}                                                  \

#define assert(condition) assert_or(condition, #condition)
#define assert_false(condition) assert_or(!(condition), #condition "is true, but should be false")

#define assert_eq(lhs, rhs) assert(lhs == rhs)
#define assert_ne(lhs, rhs) assert(lhs != rhs)

#define assert_gt(lhs, rhs) assert(lhs > rhs)
#define assert_lt(lhs, rhs) assert(lhs < rhs)

#define assert_ge(lhs, rhs) assert(lhs >= rhs)
#define assert_le(lhs, rhs) assert(lhs <= rhs)

#define start_suite(name) printf("==== START: %s\n", name)
#define end_suite(name)   printf("==== END:   %s\n\n", name)

#define start_test(name)  printf("  [*] TEST: %s\n", name)
#define end_test(name)    printf("  [*] DONE: %s\n\n", name)

#endif
