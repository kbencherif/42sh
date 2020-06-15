/*
** EPITECH PROJECT, 2019
** lib func
** File description:
** concate two str
*/

#include <stdlib.h>
#include "my.h"

char *concate(char *dest, char *src)
{
    char *new_str = NULL;
    int i = 0;
    int j = 0;

    if (!dest)
        return src;
    if (!src)
        return dest;
    new_str = malloc(my_strlen(dest) + my_strlen(src) + 1);
    for (; dest[i]; i++)
        new_str[i] = dest[i];
    while (src[j])
        new_str[i++] = src[j++];
    new_str[i] = 0;
    return new_str;
}
