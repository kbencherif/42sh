/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** main file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "my.h"
#include "shell.h"
#include "operator_abstract.h"
#include <stdio.h>
#include "env.h"
#include <string.h>

char *get_variable_string(char *str)
{
    char *variable_name = NULL;
    int i = 0;
    int y = 0;

    for (i = 0; str[i] and str[i] != '$'; i++);
    for (y = i + 1; str[y] and (is_alphanumeric(str[y])
            or str[y] is '?' or str[y] is '"' or str[y] is '\''); y++) {
        if ((str[y - 1] is '$' and (str[y] is '"' or str[y] is '\''))) {
            return NULL;
        }
        else if (not str[y + 1] and (str[y] is '"' or str[i] is '\''))
            break;
        else if (str[y] is '"')
            break;
    }
    variable_name = strndup(str + i, y - i);
    if (strlen(variable_name) is 1)
        return NULL;
    return variable_name + 1;
}

char *replace_variable(char *variable_value, char *str)
{
    int i = 0;
    int y = 0;

    for (i = 0; str[i] and str[i] != '$'; i++);
    for (int j = i; str[j]; j++)
        str[j] = str[j + 1];
    for (y = i; str[y] and (is_alphanumeric(str[y]) || str[y] is '?');)
        for (int j = y; str[j]; j++)
            str[j] = str[j + 1];
    str = insert_str(str, variable_value, i);
    return str;
}

int variable_len(variable_t **variables)
{
    int i = 0;

    for (; variables[i]; i++);
    return i;
}

void print_error(char *variable, char *variable_string, char *input)
{
    if (not variable_string)
        write(2, "Illegal variable name.\n", 23);
    else if (not variable)
        printf("%s: Undefined variable.\n", input);
}
