#include <string.h>
#include <stdio.h>
#include "mergesort.h"

int str_comparator(const void *a, const void *b) {
    return strcmp(*(const char **) a, *(const char **) b);
}

int char_comparator(const void *a, const void *b) {
    return -*(const char *) b + *(const char *) a;
}

int int_comparator(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

int main(int argc, char **argv) {

    if (argc > 2) {
        if (strcmp(argv[1], "char") == 0) {

            char *b = malloc((argc - 2) * sizeof(char));
            for (int i = 2; i < argc; i++) {
                b[i - 2] = *argv[i];
            }

            mergesort(b, argc - 2, sizeof(char), char_comparator);

            for (int i = 0; i < argc - 2; i++) {
                printf("%c ", b[i]);
            }
            printf("\n");

            free(b);

        } else {
            if (strcmp(argv[1], "str") == 0) {

                char **b = malloc((argc - 2) * sizeof(argv[2]));
                for (int i = 2; i < argc; i++) {
                    b[i - 2] = argv[i];
                }

                mergesort(b, argc - 2, sizeof(argv[2]), str_comparator);

                for (int i = 0; i < argc - 2; i++) {
                    printf("%s ", (b[i]));
                }
                printf("\n");

                free(b);

            } else {

                int *b = malloc((argc - 2) * sizeof(int));
                for (int i = 2; i < argc; i++) {
                    b[i - 2] = atoi(argv[i]);
                }

                mergesort(b, argc - 2, sizeof(int), int_comparator);

                for (int i = 0; i < argc - 2; i++) {
                    printf("%d ", b[i]);
                }
                printf("\n");

                free(b);
            }
        }
    } else {
        printf("\n");
    }
    return 0;
}