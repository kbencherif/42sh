/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** alias built_in
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"

char **cpy_doublearr(char **arr);

int get_alias_index(char *str, char ***aliases)
{
    if (!aliases)
        return -1;
    for (int i = 0; aliases[i]; i++)
        if (my_strcmp(str, aliases[i][0]))
            return i;
    return -1;
}

void change_arr(char ****old_arr, char ***new_arr)
{
    if (*old_arr)
        free(*old_arr);
    *old_arr = new_arr;
}

void delete_index(int index, char ***new_aliases, char ****aliases)
{
    int j = 0;

    for (int i = 0; (*aliases)[i]; i++) {
        if (i != index) {
            new_aliases[j] = cpy_doublearr((*aliases)[i]);
            j++;
        }
    }
    new_aliases[j] = NULL;
}

void modify_index(char ***aliases, int index, char **arg)
{
    char **new_alias = cpy_doublearr(arg);

    free(aliases[index]);
    aliases[index] = new_alias;
}
