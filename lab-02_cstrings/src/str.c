#include "str.h"

char *my_strcpy(char *restrict s1, const char *restrict s2) {
    char *initial = s1;
    while (*s2 != '\0') {
        *s1++ = *s2++;
    }
    *s1 = '\0';
    return initial;
}


char *my_strcat(char *restrict s1, const char *restrict s2) {
    char *initial = s1;
    while (*s1 != '\0') s1++;
    while (*s2 != '\0') *s1++ = *s2++;
    *s1 = '\0';
    return initial;
}


int my_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && (*s1 == *s2)) {
        s1++;
        s2++;
    }

    if (*s1 != *s2) {
//        return (*s1>*s2) ? 1 : -1;
        if (*s1 > *s2) return 1;
        else return -1;
    } else {
        return 0;
    }
}


size_t my_strlen(const char *s) {
    const char *p = s;
    while (*p != '\0') ++p;
    return (size_t) (p - s);
}


