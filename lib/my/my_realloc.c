/*
** EPITECH PROJECT, 2019
** my_realloc
** File description:
** lib func
*/

#include <unistd.h>
#include <stdlib.h>

char *my_realloc(char *str, int size)
{
    char *new_str = malloc(size);
    int i = 0;

    if (!new_str)
        return NULL;
    if (!str) {
        str = malloc(size);
        free(new_str);
        return str;
    }
    while (str[i] != '\0') {
        new_str[i] = str[i];
        i = i + 1;
    }
    new_str[i] = '\0';
    free(str);
    return new_str;
}
