#ifndef LFC_PANIC_HEADER
#define LFC_PANIC_HEADER

#include <stdio.h>
#include <stdlib.h>

#define panic(status, fmt_str, ...) fprintf(stderr, "[%s:%d @ %s] program panicked due to error:\n\t" fmt_str "\n", \
                                            __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
                                    exit(status);

#endif
