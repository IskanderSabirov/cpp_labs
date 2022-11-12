#include "test_str.h"
#include <string.h>
#include <assert.h>
#include "str.h"

void test_strcpy() {
    char std_str[30], my_str[30];
    char first[] = "123456789";
    char second[] = "0123456789";
    assert(strcmp(strcpy(std_str, first), my_strcpy(my_str, first)) == 0);
    assert(strcmp(strcpy(std_str, second), my_strcpy(my_str, first)) != 0);
}

void test_strcmp() {
    char first[] = "123456789";
    char second[] = "0123456789";
    assert(strcmp(first, first) == my_strcmp(first, first));
    assert(strcmp(first, second) == my_strcmp(first, second));
    assert(strcmp(second, first) == my_strcmp(second, first));
}

void test_strcat() {
    char first[60] = "123456789";
    char third[60] = "123456789";
    char second[30] = "0123456789";
    assert(strcmp(strcat(first, second), my_strcat(first, second)) == 0);
    assert(strcmp(strcat(first, third), my_strcat(first, third)) == 0);
    assert(strcmp(strcat(third, second), my_strcat(third, second)) == 0);
}

void test_strlen() {
    char first[] = "123456789";
    char second[] = "0123456789";
    char third[] = "9876543210";
    assert(strlen(first) != my_strlen(second));
    assert(strlen(third) == my_strlen(second));
    assert(strlen(third) != my_strlen(first));
}






