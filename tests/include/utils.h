#ifndef LFC_ASSERT_HEADER
#define LFC_ASSERT_HEADER

#include "lfc/utils/panic.h"

#include <stdio.h>
#include <string.h>

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

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define start_suite() printf("==== START: %s\n", __FILENAME__)
#define end_suite()   printf("==== END:   %s\n\n", __FILENAME__)

#define start_test()  printf("  [+] TEST: %s\n", __FUNCTION__)
#define end_test()    printf("  [-] DONE: %s\n", __FUNCTION__)

#endif
