#include "lfc/utils/mem.h"

int main() {
    char* buf = malloc_unwrap(sizeof(char), 3, "failed to alloc");
    free(buf);

    return 0;
}
