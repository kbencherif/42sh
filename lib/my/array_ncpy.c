/*
** EPITECH PROJECT, 2020
** array_cpy.c
** File description:
** copy char **
*/

#include "my.h"
#include <stdlib.h>

char **array_ncpy(char **array, int len)
{
    char **new_array = NULL;

    new_array = malloc(sizeof(char *) * (len + 1));
    new_array[len] = NULL;
    for (int i = 0; array[i] && i < len; i++)
        new_array[i] = my_strdup(array[i]);
    return new_array;
}
