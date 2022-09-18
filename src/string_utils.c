#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include "./string_utils.h"

bool string_equals(char* s1, char* s2) 
{
    if (!s1) {
        fprintf(stderr, "Cannot evaluate as string: NULL == %s", s2);
        exit(EXIT_FAILURE);
    }

    if (!s2) {
        fprintf(stderr, "Cannot evaluate as string: %s == NULL", s1);
        exit(EXIT_FAILURE);
    }

    return strcmp(s1, s2) == 0;
}

char* string_to_upper(char* s)
{
    assert(s && "Could not make uppercase null string");

    size_t length = strlen(s);

    for (size_t i = 0; i < length; i++) {
        s[i] = toupper(s[i]);
    }

    return s;
}

bool is_bool(char c)
{
    return c == '0' || c == '1';
}