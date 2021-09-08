#include "lfc/utils/pair.h"

#include "lfc/utils/mem.h"

void pair_init(pair_t* pair, void* first, void* second) {
    pair->first = first;
    pair->second = second;
}

void pair_free(pair_t* pair, free_fn_t first_free, free_fn_t second_free) {
    first_free(&pair->first);
    second_free(&pair->second);
}
