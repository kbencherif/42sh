/*
** EPITECH PROJECT, 2020
** array_cpy.c
** File description:
** copy char **
*/

#include "my.h"
#include <stdlib.h>

char **array_cpy(char **array)
{
    int size = 0;
    char **new_array = NULL;

    for (; array[size]; size++);
    new_array = malloc(sizeof(char *) * (size + 1));
    new_array[size] = NULL;
    for (int i = 0; array[i]; i++)
        new_array[i] = my_strdup(array[i]);
    return new_array;
}
