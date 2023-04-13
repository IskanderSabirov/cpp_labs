#include "mergesort.h"
#include <malloc.h>
#include <assert.h>

static void assign(char *string, char *string1, size_t size);

static void merge_sort(void *array, int l, int r, size_t element_size, int (*comparator)(const void *, const void *));

static void
merge_segments(void *array, int l, int m, int r, size_t element_size, int (*comparator)(const void *, const void *));


// основаная функция
void mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *)) {
    merge_sort(array, 0, elements, element_size, comparator);
}


static void assign(char *string, char *string1, size_t size) {
    int i = 0;
    while ((size_t) i < size) {
        *(string + i) = *(string1 + i);
        i++;
    }
}

static void merge_sort(void *array, int l, int r, size_t element_size,
                       int (*comparator)(const void *, const void *)) {
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    merge_sort(array, l, m, element_size, comparator);
    merge_sort(array, m, r, element_size, comparator);
    merge_segments(array, l, m, r, element_size, comparator);
}


void merge_segments(void *array, int l, int m, int r, size_t element_size,
                    int (*comparator)(const void *, const void *)) {
    char *b = malloc((r - l) * element_size);
    char *p = (char *) array;
    assert(b != NULL);
    int i = l, j = m, k = 0;
    while (i < m || j < r) {
        if (j >= r || (i < m && (comparator(p + i * element_size, p + j * element_size) <= 0))) {
            assign(b + k * element_size, p + i * element_size, element_size);
            i++;
        } else {
            assign(b + k * element_size, p + j * element_size, element_size);
            j++;
        }
        k++;
    }
    i = 0;
    while (i < (r - l)) {
        assign(p + l * element_size + i * element_size, b + i * element_size, element_size);
        i++;
    }
    free(b);
}

