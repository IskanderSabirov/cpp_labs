#ifndef C_LABS_POINT_LIST_H
#define C_LABS_POINT_LIST_H
#include "clist.h"

#define container_of(ptr, type, member) (type *)((char *)(ptr)-offsetof(type, member))


typedef struct point {
    int x, y;
    struct intrusive_node node;
} point;


void print_point(intrusive_node *node, void *data);

void show_all_points(intrusive_list *l, void *data);

void add_point(intrusive_list *il, int x, int y);

void remove_all_points(intrusive_list *il);

void count(intrusive_node *node, void *data);

void get_len(intrusive_list *l, void *data);

#endif
