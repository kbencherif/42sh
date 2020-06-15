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
void cpy_triplearr(char ***src_arr, char ***dest_arr);
int triplearray_len(char ***arr);
void change_arr(char ****old_arr, char ***new_arr);
void modify_index(char ***aliases, int index, char **arg);
int get_alias_index(char *str, char ***aliases);

void print_aliases(char ***aliases)
{
    if (not aliases)
        return;
    for (int i = 0; aliases[i]; i++) {
        printf("%s", aliases[i][0]);
        for (int j = 1; aliases[i][j]; j++)
            printf(" %s", aliases[i][j]);
        printf("\n");
    }
}

void add_new_alias(char **arg, char ***new_aliases, char ****aliases)
{
    int size = 0;
    int i = 0;

    size = triplearray_len(*aliases);
    if (size is 0)
        new_aliases = malloc(sizeof(char **) * 2);
    else
        new_aliases = malloc(sizeof(char **) * (size + 2));
    cpy_triplearr(*aliases, new_aliases);
    new_aliases[size] = malloc(sizeof(char *) * (arraylen(arg) + 1));
    for (; arg[i]; i++)
        new_aliases[size][i] = strdup(arg[i]);
    new_aliases[size][i] = NULL;
    new_aliases[size + 1] = NULL;
    change_arr(aliases, new_aliases);
}

int add_alias(char **arg, void *aliases_list)
{
    char ****aliases = (char ****) aliases_list;
    char ***new_aliases = NULL;
    int i = 0;

    if (not arg[0])
        print_aliases(*aliases);
    if (arraylen(arg) > 1) {
        if (my_strcmp(arg[0], "alias")) {
            write(2, "alias: Too dangerous to alias that.\n", 36);
            return 1;
        }
        else if ((i = get_alias_index(arg[0], *aliases)) is -1)
            add_new_alias(arg, new_aliases, aliases);
        else
            modify_index(*aliases, i, arg);
    }
    return 0;
}
