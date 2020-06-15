/*
** EPITECH PROJECT, 2019
** my_strdup
** File description:
** task01
*/

#include <stdlib.h>

static int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != 0) {
        i++;
    }
    return (i);
}

static char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i = i + 1;
    }
    dest[i] = '\0';
    return (dest);
}

char *my_strdup(char const *src)
{
    int size = 0;
    char *dest;

    size = my_strlen(src);
    dest = malloc(sizeof(char) * size + 1);
    my_strcpy(dest, src);
    return (dest);
}
