#ifndef C_LABS_CLIST_H
#define C_LABS_CLIST_H
#include <stddef.h>

typedef struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
} intrusive_node;

typedef struct intrusive_list {
    intrusive_node *head;
    intrusive_node *tail;
} intrusive_list;

void init(intrusive_list *list);

void add_node(intrusive_list *list, intrusive_node *addNode);

void remove_node(intrusive_list *list, intrusive_node *removeNode);

void apply(intrusive_list *list, void (*op)(intrusive_node *node, void *data), void *data);

#endif
