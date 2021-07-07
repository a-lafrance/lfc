#include "lfc/utils/optional.h"
#include "lfc/utils/panic.h"

void option_init(option_t* option, void* data) {
    option->data = data;
}

option_t option_null() {
    option_t option;
    option->data = NULL;

    return option;
}

int option_is_some(option_t* option) {
    return option != NULL;
}

int option_is_null(option_t* option) {
    return option == NULL;
}

void* option_unwrap(option_t* option) {
    if (option_is_some(option)) {
        return option->data;
    }
    else {
        panic(1, "[option_t] attempted to unwrap a null value");
    }
}
