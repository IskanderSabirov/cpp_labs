#include "point_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


void add_point(intrusive_list *list, int x, int y) {
    point *p = (point *) malloc(sizeof(point));
    assert(p);
    p->x = x;
    p->y = y;
    add_node(list, &(p->node));
}


void print_point( intrusive_node *node, void *data) {
    point *p = container_of(node, point, node);
    char *form = data;
    printf(form, p->x, p->y);
}


void show_all_points( intrusive_list *l, void *data) {
    apply(l, print_point, data);
    printf("\n");
}


void remove_all_points(intrusive_list *list) {
    intrusive_node *base = list->head;

    while (base != NULL) {

        intrusive_node *nowNode = base;
        base = base->next;

        point *remove_point = container_of(nowNode, point, node);

        remove_node(list, nowNode);
        free(remove_point);
    }
}


void count( intrusive_node *node, void *data) {
    if (node) {
        int *sum = data;
        (*sum)++;
    }
}


void get_len( intrusive_list *l, void *data) {
    apply(l, count, data);
}