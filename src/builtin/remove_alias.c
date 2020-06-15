/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** alias built_in
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "operator_abstract.h"
#include "my.h"

int arraylen(char **array);
int triplearray_len(char ***arr);
void change_arr(char ****old_arr, char ***new_arr);
void delete_index(int index, char ***new_aliases, char ****aliases);
int get_alias_index(char *str, char ***aliases);

char ***malloc_arr(int size, char ****aliases)
{
    char ***new_aliases = NULL;

    if ((size = triplearray_len(*aliases)) > 1)
        new_aliases = malloc(sizeof(char **) * size);
    else if (size is 1)
        new_aliases = malloc(sizeof(char **) * 1);
    return new_aliases;
}

int remove_alias(char **arg, void *aliases_list)
{
    char ****aliases = (char ****) aliases_list;
    char ***new_aliases = NULL;
    int i = 0;
    int size = 0;

    if (not arg[0]) {
        write(2, "unalias: Too few arguments.\n", 28);
        return 1;
    }
    if (not aliases_list)
        return 0;
    new_aliases = malloc_arr(size, aliases);
    for (int j = 0; arg[j]; j++) {
        i = get_alias_index(arg[j], *aliases);
        if (i >= 0) {
            delete_index(i, new_aliases, aliases);
            change_arr(aliases, new_aliases);
        }
    }
    return 0;
}
