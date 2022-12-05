#include "clist.h"
#include <stddef.h>


void init(intrusive_list *my_list) {

    my_list->head = NULL;

}

void add_node(intrusive_list *my_list, intrusive_node *node) {

    if (my_list->head == NULL) {
        node->prev = NULL;
        node->next = NULL;
        my_list->head = node;
    } else {
        node->next = my_list->head;
        node->prev = NULL;
        my_list->head->prev = node;
        my_list->head = node;
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

int get_length(intrusive_list *my_list) {

    intrusive_node *base = my_list->head;
    int size = 0;

    while (base != NULL) {
        base = base->next;
        size++;
    }

    return size;
}


