/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** alias built_in
*/

#include <string.h>
#include "my.h"
#include "operator_abstract.h"

int get_alias_index(char *str, char ***aliases);
int arraylen(char **arr);

bool is_reverse(char **arr1, char **arr2, int index1, int index2)
{
    int j = 0;

    if (index1 is index2)
        return false;
    if (arraylen(arr1) isnt arraylen(arr2))
        return false;
    for (; arr2[j]; j++);
    j--;
    for (int i = 0; arr1[i]; i++, j--)
        if (not my_strcmp(arr1[i], arr2[j]))
            return false;
    return true;
}

bool is_alias_loop(char **arg, char ***aliases)
{
    int index = 0;

    if (!aliases)
        return false;
    index = get_alias_index((arg[0]), aliases);
    for (int i = 0; aliases[i]; i++) {
        if (is_reverse(aliases[index], aliases[i], index, i))
            return true;
    }
    return false;
}
