#include "clist.h"
#include <stddef.h>


void init(intrusive_list *my_list) {

    my_list->head = NULL;
    my_list->tail = NULL;

}


void add_node(intrusive_list *my_list, intrusive_node *node) {
    if (my_list->tail == NULL) {

        node->prev = NULL;
        node->next = NULL;
        my_list->head = node;
        my_list->tail = node;

    } else {

        node->prev = my_list->tail;
        my_list->tail->next = node;
        my_list->tail = node;
        node->next = NULL;

    }
}


void remove_node(intrusive_list *list, intrusive_node *node) {

    if (node->prev == NULL) {

        list->head = node->next;

        if (node->next != NULL) node->next->prev = NULL;

    } else {

        node->prev->next = node->next;

        if (node->next != NULL) node->next = node->prev;

    }
}


void apply(intrusive_list *list, void (*op)(intrusive_node *node, void *data), void *data) {

    intrusive_node *base = list->head;

    while (base != NULL) {
        op(base, data);
        base = base->next;
    }
}