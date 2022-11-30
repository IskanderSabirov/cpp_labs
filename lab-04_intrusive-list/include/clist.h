#ifndef CLIST_H_
#define CLIST_H_

#include <stddef.h>

typedef struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
} intrusive_node;

typedef struct intrusive_list {
    intrusive_node *head;
} intrusive_list;

void init(intrusive_list *list);

void add_node(intrusive_list *list, intrusive_node *addNode);

void remove_node(intrusive_list *list, intrusive_node *removeNode);

int get_length(intrusive_list *list);

#endif
