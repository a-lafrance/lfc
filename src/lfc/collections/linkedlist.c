#include "lfc/collections/linkedlist.h"
#include "lfc/utils/mem.h"

#include <stdlib.h>

void ll_node_init(struct ll_node* node, struct ll_node* next, void* data) {
    node->next = next;
    node->data = data;
}

void ll_init(list_t* list) {
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

void ll_free(list_t* list, void (*elem_free)(void*)) {
    struct ll_node* current = list->head;

    while (current != NULL) {
        // free data if necessary
        if (elem_free != NULL) {
            (*elem_free)(current->data);
        }

        // advance to next node
        struct ll_node* prev = current;
        current = current->next;

        // free current node
        free(prev);
    }
}

void ll_append(list_t* list, void* elem) {
    struct ll_node* node = malloc_unwrap(sizeof(struct ll_node), 1, "[ll_append] failed to alloc new node");
    ll_node_init(node, NULL, elem);

    if (list->head == NULL) {
        list->head = node;
    }
    else {
        list->tail->next = node;
    }

    list->tail = node;
}

void ll_prepend(list_t* list, void* elem) {
    struct ll_node* node = malloc_unwrap(sizeof(struct ll_node), 1, "[ll_prepend] failed to alloc new node");
    ll_node_init(node, list->head, elem);

    if (list->head == NULL) {
        list->tail = node;
    }

    list->head = node;
}

size_t ll_find(list_t* list, void* target, int (*elem_eq)(void*, void*)) {
    size_t i = 0;

    for (struct ll_node* node = list->head; node != NULL; node = node->next) {
        if (elem_eq(node->data, target)) {
            return i;
        }

        i++;
    }

    return -1;
}
