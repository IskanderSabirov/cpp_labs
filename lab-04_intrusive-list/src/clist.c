#include "../include/clist.h"
#include <stdlib.h>
#include "stddef.h"


void init(intrusive_list *my_list) {

    my_list->head = malloc(sizeof(intrusive_node));
    my_list->head->prev = my_list->head->next = NULL;

}

void add_node(intrusive_list *my_list, intrusive_node *node) {

    intrusive_node *base = my_list->head;

    if (base->next != NULL) {
        intrusive_node *next = base->next;
        base->next = node;
        node->prev = base;
        node->next = next;
        next->prev = node;
    } else {
        base->next = node;
        base->next->prev = base;
        base->next->next = NULL;
    }
}

void remove_node(intrusive_node *node) {

    intrusive_node *previous = node->prev;

    if (node->next != NULL) {
        previous->next = node->next;
        node->next->prev = previous;
    } else {
        previous->next = NULL;
    }
}

int get_length(intrusive_list *my_list) {

    intrusive_node *base = my_list->head;
    int size = 0;

    while (base->next != NULL) {
        base = base->next;
        size++;
    }

    return size;
}


