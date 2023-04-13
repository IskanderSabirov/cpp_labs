#ifndef C_LABS_MERGESORT_H
#define C_LABS_MERGESORT_H

#include <stddef.h>

void mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *));

#endif
