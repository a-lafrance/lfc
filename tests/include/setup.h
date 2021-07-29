#ifndef LFC_TESTS_SETUP_HEADER
#define LFC_TESTS_SETUP_HEADER

#include <stdio.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define start_suite() printf("==== START: %s\n", __FILENAME__)
#define end_suite()   printf("==== END:   %s\n\n", __FILENAME__)

#define start_test()  printf("  [+] TEST: %s\n", __FUNCTION__)
#define end_test()    printf("  [-] DONE: %s\n", __FUNCTION__)

#endif
