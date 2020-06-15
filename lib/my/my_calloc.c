/*
** EPITECH PROJECT, 2019
** my_calloc
** File description:
** my_calloc
*/

#include <stdlib.h>

void *my_calloc(int size)
{
    char *str = malloc(sizeof(char) * size);

    for (int i = 0; i < size; i++)
        str[i] = 0;
    return str;
}
