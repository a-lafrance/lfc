#include "utils.h"

#include "lfc/utils/mem.h"

#include <stdlib.h>
#include <string.h>

void something_init(struct something* thing, int n) {
    thing->n = malloc_unwrap(sizeof(int), 1, "[struct something] failed to alloc int field");
    *thing->n = n;
}

void something_init_zeroed(struct something* thing) {
    thing->n = calloc_unwrap(sizeof(int), 1, "[struct something] failed to alloc int field");
}

void something_free(struct something* thing) {
    struct something* something = thing;
    free(something->n);
}

int int_eq(void* lhs, void* rhs) {
   return *(int*)lhs == *(int*)rhs;
}

int barestr_eq(void* lhs, void* rhs) {
    return strcmp(lhs, rhs) == 0;
}

void barestr_free(char* str) {
    free(str);
}
