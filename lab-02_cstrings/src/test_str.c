#include "test_str.h"
#include <string.h>
#include <assert.h>
#include "str.h"

void test_strcpy() {
    char std_str[30], my_str[30];
    char first[] = "123456789";
    char second[] = "0123456789";
    char third[] = "";

    assert(strcmp(strcpy(std_str, first), my_strcpy(my_str, first)) == 0);
    assert(strcmp(my_str, first) == 0);
    assert(strcmp(my_str, std_str) == 0);

    assert(strcmp(strcpy(std_str, second), my_strcpy(my_str, second)) == 0);
    assert(strcmp(my_str, second) == 0);
    assert(strcmp(my_str, std_str) == 0);

    assert(strcmp(strcpy(std_str, third), my_strcpy(my_str, third)) == 0);
    assert(strcmp(my_str, third) == 0);
    assert(strcmp(my_str, std_str) == 0);

    char *my_result = my_strcpy(my_str, first);
    assert(my_result == my_str);

}

void test_strcmp() {
    char first[] = "123456789";
    char second[] = "0123456789";

    assert(strcmp(first, first) == my_strcmp(first, first));
    assert(strcmp(first, second) == my_strcmp(first, second));
    assert(strcmp(second, first) == my_strcmp(second, first));
    assert(my_strcmp("a", "") > 0);
    assert(my_strcmp("", "a") < 0);
    assert(my_strcmp("", "") == 0);
    assert(my_strcmp("acd", "bcd") < 0);
    assert(my_strcmp("acd", "acd") == 0);
    assert(my_strcmp("acd", "acde") < 0);
    assert(my_strcmp("acdef", "acde") > 0);
    assert(my_strcmp("acdfe", "acdee") > 0);
}

void test_strcat() {
    char first[60] = "123456789";
    char third[60] = "123456789";
    char second[30] = "0123456789";
    assert(strcmp(strcat(first, second), my_strcat(first, second)) == 0);
    assert(strcmp(strcat(first, third), my_strcat(first, third)) == 0);
    assert(strcmp(strcat(third, second), my_strcat(third, second)) == 0);

    char *my_result1 = my_strcat(first, second);
    assert(my_result1 == first);

    char *my_result2 = my_strcat(third, second);
    assert(my_result2 == third);


}

void test_strlen() {
    char first[] = "123456789";
    char second[] = "0123456789";
    char third[] = "9876543210";
    assert(strlen(first) != my_strlen(second));
    assert(strlen(third) == my_strlen(second));
    assert(strlen(third) != my_strlen(first));
}






