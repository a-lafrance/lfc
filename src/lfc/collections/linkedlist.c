#include "lfc/collections/linkedlist.h"
#include "lfc/utils/optional.h"

#include <stdlib.h>

void ll_init(list_t* list) {
    list->head = option_null();
    list->tail = option_null();
    list->len = 0;
}

void ll_free(list_t* list, void (*elem_free)(void*)) {
    option_t current = list->head;

    while (option_is_some(current)) {
        struct ll_node* node = current.unwrap();

        // free data if necessary
        if (elem_free != NULL) {
            (*elem_free)(node->data);
        }

        // advance to next node
        current = node->next;

        // free current node
        free(node);
    }
}

void ll_append(list_t* list, void* elem) {
    struct ll_node* node = malloc(sizeof(struct ll_node));
}

size_t ll_find(list_t* list, void* target, void (*elem_eq)(void*, void*)) {

}
