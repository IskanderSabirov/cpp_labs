#include "clist.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

#define container_of(ptr, type, member) (type *)((char *)(ptr)-offsetof(type, member))

typedef struct point {
    int x, y;
    struct intrusive_node node;
} point;

void add_point(intrusive_list *my_list, int x, int y) {
    point *p = (point *) malloc(sizeof(point));
    p->x = x;
    p->y = y;
    add_node(my_list, &(p->node));
}


void remove_point(intrusive_list *my_list, int x, int y) {

    intrusive_node *head = my_list->head;


    while (head->next != NULL) {

        intrusive_node *nowNode = head->next;

        point *remove_point = container_of(nowNode, point, node);

        if (!(remove_point->x == x && remove_point->y == y)) {
            head = head->next;
            continue;
        }

        remove_node(nowNode);
        free(remove_point);
    }
}


void show_all_points(intrusive_list *my_list) {
    intrusive_node *base = my_list->head;
    while (base->next != NULL) {

        base = base->next;
        point *print_point = container_of(base, point, node);

        if (base->next != NULL) {
            printf("(%d %d) ", print_point->x, print_point->y);
        } else printf("(%d %d)\n", print_point->x, print_point->y);
    }
}


void remove_all_points(intrusive_list *my_list) {
    intrusive_node *base = my_list->head;

    while (base->next != NULL) {

        intrusive_node *nowNode = base->next;
        point *remove_point = container_of(nowNode, point, node);

        remove_node(nowNode);
        free(remove_point);
    }
}

int main() {
    intrusive_list my_list;
    init(&my_list);

    char arguments[239];
    int x, y;

    while (true) {

        scanf("%239s", arguments);

        if (strcmp(arguments, "add") == 0) {

            scanf("%d %d", &x, &y);
            add_point(&my_list, x, y);

        } else if (strcmp(arguments, "rm") == 0) {

            scanf("%d %d", &x, &y);
            remove_point(&my_list, x, y);

        } else if (strcmp(arguments, "len") == 0) {

            printf("%d\n", get_length(&my_list));

        } else if (strcmp(arguments, "rma") == 0) {

            remove_all_points(&my_list);

        } else if (strcmp(arguments, "print") == 0) {

            show_all_points(&my_list);

        } else if (strcmp(arguments, "exit") == 0) {

            break;

        } else {

            printf("Unknown command\n");

        }
    }

    remove_all_points(&my_list);
    free(my_list.head);
    return 0;
}
