#include <stdio.h>
#include <stdbool.h>
#include "strlib.h"

void test_str_construct()
{
    String s = str_construct("Hello");
    printf("Test str_construct: %s\n", s.data);
    str_destruct(s);
}

void test_str_concat()
{
    String s1 = str_construct("Hello");
    String s2 = str_construct(" World");
    String result = str_concat(s1, s2);
    printf("Test str_concat: %s\n", result.data);
    str_destruct(s1);
    str_destruct(s2);
    str_destruct(result);
}

void test_str_toUpperCase()
{
    String s = str_construct("Hello");
    String result = str_toUpperCase(s);
    printf("Test str_toUpperCase: %s\n", result.data);
    str_destruct(s);
    str_destruct(result);
}

void test_str_toLowerCase()
{
    String s = str_construct("HELLO");
    String result = str_toLowerCase(s);
    printf("Test str_toLowerCase: %s\n", result.data);
    str_destruct(s);
    str_destruct(result);
}

void test_str_trim()
{
    String s = str_construct("   Hello   ");
    String result = str_trim(s);
    printf("Test str_trim: '%s'\n", result.data);
    str_destruct(s);
    str_destruct(result);
}

void test_str_indexOf()
{
    String s = str_construct("Hello World");
    String search = str_construct("World");
    int index = str_indexOf(s, search);
    printf("Test str_indexOf: %d\n", index);
    str_destruct(s);
    str_destruct(search);
}

int main()
{
    test_str_construct();
    test_str_concat();
    test_str_toUpperCase();
    test_str_toLowerCase();
    test_str_trim();
    test_str_indexOf();

    return 0;
}
