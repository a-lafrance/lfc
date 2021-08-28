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

void ll_free(list_t* list, free_fn_t elem_free) {
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

void* ll_first(list_t* list) {
    return list->head != NULL ? list->head->data : NULL;
}

void* ll_last(list_t* list) {
    return list->tail != NULL ? list->tail->data : NULL;
}

void ll_append(list_t* list, void* elem) {
    struct ll_node* node = malloc_unwrap(sizeof(struct ll_node), 1, "[ll_append] failed to alloc new node");
    ll_node_init(node, NULL, elem);

    if (list->head == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
    list->len += 1;
}

void ll_prepend(list_t* list, void* elem) {
    struct ll_node* node = malloc_unwrap(sizeof(struct ll_node), 1, "[ll_prepend] failed to alloc new node");
    ll_node_init(node, list->head, elem);

    if (list->head == NULL) {
        list->tail = node;
    }

    list->head = node;
    list->len += 1;
}

void* ll_pop_first(list_t* list) {
    if (ll_is_empty(list)) {
        return NULL;
    } else {
        struct ll_node* first = list->head;
        void* elem = first->data;

        list->head = list->head->next;
        list->len -= 1;

        if (list->head == NULL) {
            list->tail = NULL;
        }

        free(first);

        return elem;
    }
}

int ll_find(list_t* list, void* target, int (*elem_eq)(void*, void*)) {
    for (struct ll_node* node = list->head; node != NULL; node = node->next) {
        if (elem_eq(node->data, target)) {
            return 1;
        }
    }

    return 0;
}

void* ll_remove(list_t* list, void* target, int (*elem_eq)(void*, void*)) {
    struct ll_node* prev = NULL;

    for (struct ll_node* node = list->head; node != NULL; node = node->next) {
        void* elem = node->data;

        if (elem_eq(elem, target)) {
            if (prev != NULL) {
                prev->next = node->next;
            } else {
                list->head = node->next;
            }

            if (node->next == NULL) {
                list->tail = NULL;
            }

            list->len -= 1;

            return elem;
        }
    }

    return NULL;
}

int ll_is_empty(list_t* list) {
    return list->len == 0;
}
