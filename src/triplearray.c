/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** triple array manipulation file
*/

#include <stdlib.h>
#include <string.h>

int arraylen(char **array);

int triplearray_len(char ***arr)
{
    int size = 0;

    if (!arr)
        return 0;
    for (; arr[size]; size++);
    return size;
}

char **cpy_doublearr(char **arr)
{
    int i = 0;
    char **cpd_arr = malloc(sizeof(char *) * (arraylen(arr) + 1));

    for (; arr[i]; i++)
        cpd_arr[i] = strdup(arr[i]);
    cpd_arr[i] = NULL;
    return cpd_arr;
}

void cpy_triplearr(char ***src_arr, char ***dest_arr)
{
    if (!src_arr)
        return;
    for (int i = 0; src_arr[i]; i++)
        dest_arr[i] = src_arr[i];
}
