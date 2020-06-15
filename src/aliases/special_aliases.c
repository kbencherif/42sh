/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** alias built_in
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "my.h"

int get_alias_index(char *str, char ***aliases);
int exec_line(char *lineptr, shell_t *shell, char *escape_char);

void special_aliases(shell_t *shell, char *escape_char, char *alias)
{
    char *special_alias = strdup(alias);

    if (get_alias_index(special_alias, shell->aliases) >= 0)
        exec_line(special_alias, shell, escape_char);
}
