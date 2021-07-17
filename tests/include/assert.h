#ifndef LFC_ASSERT_HEADER
#define LFC_ASSERT_HEADER

#include "lfc/utils/panic.h"

#define assert_or(condition, msg)                  \
if (!(condition)) {                                \
    panic(1, "assertion failed: %s", msg);         \
}                                                  \

#define assert(condition) assert_or(condition, #condition)
#define assert_false(condition) assert_or(!(condition), #condition "is true")

#define assert_eq(lhs, rhs) assert(lhs == rhs)
#define assert_ne(lhs, rhs) assert(lhs != rhs)

#define assert_gt(lhs, rhs) assert(lhs > rhs)
#define assert_lt(lhs, rhs) assert(lhs < rhs)

#define assert_ge(lhs, rhs) assert(lhs >= rhs)
#define assert_le(lhs, rhs) assert(lhs <= rhs)

#endif
