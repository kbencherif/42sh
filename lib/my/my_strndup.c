/*
** EPITECH PROJECT, 2019
** strndup
** File description:
** strndup
*/

#include <stdlib.h>

char *my_strncpy(char *dest, char const *src, int n);

char *my_strndup(char *str, int len)
{
    char *new_str = malloc(len + 1);

    new_str[len] = 0;
    my_strncpy(new_str, str, len);
    return new_str;
}
