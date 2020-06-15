/*
** EPITECH PROJECT, 2019
** free double array
** File description:
** lib func
*/

#include <stdlib.h>

void free_double_array(char **array)
{
    for (int i = 0; (array)[i]; i++)
        free((array)[i]);
    free(array);
}
