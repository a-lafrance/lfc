#include "lfc/utils/pair.h"
#include "lfc/utils/mem.h"

void pair_init(pair_t* pair, void* first, void* second) {
    pair->first = first;
    pair->second = second;
}

void pair_free(pair_t* pair, free_fn_t first_free, free_fn_t second_free) {
    if (first_free != NULL) {
        first_free(pair->first);
    }

    if (second_free != NULL) {
        second_free(pair->second);
    }
}
