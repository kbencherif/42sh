/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** alias built_in
*/

#include <string.h>
#include "my.h"
#include "operator_abstract.h"

int arraylen(char **array);

void substitute_alias(char **alias, char ***args)
{
    char **new_arr = malloc(sizeof(char *) *
            (arraylen(alias) + arraylen((*args) + 1) + 1));
    int i = 0;

    if (!new_arr)
        return;
    for (int j = 1; alias[j]; i++, j++)
        new_arr[i] = alias[j];
    for (int j = 1; (*args)[j]; i++, j++)
        new_arr[i] = (*args)[j];
    new_arr[i] = NULL;
    *args = new_arr;
}

void change_alias(char ***arg, char ***aliases)
{
    if (not aliases)
        return;
    for (int i = 0; aliases[i]; i++)
        if (my_strcmp(aliases[i][0], (*arg)[0])) {
            substitute_alias(aliases[i], arg);
            break;
        }
}

bool is_alias(char *cmd, char ***aliases)
{
    for (int i = 0; aliases[i]; i++)
        if (my_strcmp(aliases[i][0], cmd))
            return true;
    return false;
}

bool is_there_alias(char **arg, char ***aliases)
{
    if (!aliases)
        return false;
    for (int i = 0; arg[i]; i++) {
        if (is_alias(arg[0], aliases))
            return true;
    }
    return false;
}
