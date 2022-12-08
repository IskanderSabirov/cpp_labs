#include "clist.h"
#include "point_list.h"
#include <stdio.h>
#include <string.h>

#define container_of(ptr, type, member) (type *)((char *)(ptr)-offsetof(type, member))

void read_txt(FILE *f, intrusive_list *list) {

    int x, y;

    while (fscanf(f, "%d %d", &x, &y) == 2) {
        add_point(list, x, y);
    }

}


void read_bin(FILE *f, intrusive_list *l) {
    int x, y;

    fread(&(x), 3, 1, f);
    if (x > 0x7FFFFF) {
        x = x - 0x1000000;
    }

    fread(&(y), 3, 1, f);
    if (y > 0x7FFFFF) {
        y = y - 0x1000000;
    }

    add_point(l, x, y);

    x=0;
    y=0;
}

void write_txt(FILE *f, intrusive_list *l) {
    intrusive_node *cur = l->head;
    while (cur) {
        point *p = container_of(cur, point, node);
        fprintf(f, "%d %d\n", p->x, p->y);
        cur = cur->next;
    }
}


void write_bin(FILE *f, intrusive_list *l) {
    intrusive_node *cur = l->head;

    while (cur) {

        point *p = container_of(cur, point, node);
        if ((p->x) >= 0) {
            fwrite(&(p->x), 3, 1, f);
        } else {
            int k = 0x1000000 + (p->x);
            fwrite(&k, 3, 1, f);
        }
        if ((p->y) >= 0) {
            fwrite(&(p->y), 3, 1, f);
        } else {
            int k = 0x1000000 + (p->y);
            fwrite(&k, 3, 1, f);
        }

        cur = cur->next;
    }
}


int main(int argc, char *argv[]) {

    intrusive_list l;

    init(&l);

    if ((argc > 0) && (strcmp(argv[1], "loadtext") == 0)) {
        FILE *f = fopen(argv[2], "r");
        read_txt(f, &l);
        fclose(f);
    }

    if ((argc > 0) && (strcmp(argv[1], "loadbin") == 0)) {
        FILE *f = fopen(argv[2], "r");
        read_bin(f, &l);
        fclose(f);
    }
    if ((argc > 2) && (strcmp(argv[3], "count") == 0)) {
        int s = 0;
        get_len(&l, &s);
        printf("%d\n", s);
    }

    if ((argc > 2) && (strcmp(argv[3], "print") == 0)) {
        show_all_points(&l, argv[4]);
    }

    if ((argc > 2) && (strcmp(argv[3], "savetext") == 0)) {
        FILE *f = fopen(argv[4], "w");
        write_txt(f, &l);
        fclose(f);
    }

    if ((argc > 2) && (strcmp(argv[3], "savebin") == 0)) {
        FILE *f = fopen(argv[4], "w");
        write_bin(f, &l);
        fclose(f);
    }

    remove_all_points(&l);
    return 0;
}
