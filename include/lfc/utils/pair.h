#ifndef LFC_PAIR_HEADER
#define LFC_PAIR_HEADER

#include "lfc/utils/mem.h"

typedef struct {
    void* first;
    void* second;
} pair_t;

void pair_init(pair_t* pair, void* first, void* second);
void pair_free(pair_t* pair, free_fn_t first_free, free_fn_t second_free);

#endif
