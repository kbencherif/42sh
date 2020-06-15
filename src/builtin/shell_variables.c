/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** shell variables
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "shell.h"
#include "operator_abstract.h"
#include <stdio.h>
#include "env.h"

int variable_len(variable_t **variables);
void clean_quote(char **str);
void print_error(char *variable, char *variable_string, char *input);

char **replace_shell_variable(char **parsed_cmd,
                                shell_t *shell,
                                int i)
{
    char *variable = NULL;
    char *variable_string = NULL;

    while (strstr(parsed_cmd[i], "$") && strlen(parsed_cmd[i]) > 1) {
        variable_string = get_variable_string(parsed_cmd[i]);
        if ((variable = get_variable(shell, variable_string))) {
            parsed_cmd[i] = replace_variable(variable, parsed_cmd[i]);
        } else if ((variable = my_getenv(variable_string, shell->env))) {
            parsed_cmd[i] = replace_variable(variable, parsed_cmd[i]);
        } else {
            print_error(variable, variable_string, parsed_cmd[i]);
            return NULL;
        }
    }
    return parsed_cmd;
}

bool change_variable(shell_t *shell, char *name, char *value)
{
    for (int i = 0; shell->variables[i]; i++) {
        if (my_strcmp(shell->variables[i]->name, name) and value) {
            shell->variables[i]->value = strdup(value);
            return true;
        }
        else if (my_strcmp(shell->variables[i]->name, name) and not value) {
            shell->variables[i]->value = strdup("\0");
            return true;
        }
    }
    return false;
}

void add_variable(shell_t *shell, char *name, char *value)
{
    int len = 0;

    if (shell->variables and change_variable(shell, name, value))
        return;
    if (not shell->variables) {
        shell->variables = malloc(sizeof(variable_t *) * 2);
    } else {
        for (; shell->variables and shell->variables[len]; len++);
        shell->variables = realloc(shell->variables,
                                sizeof(variable_t *) * (len + 2));
    }
    shell->variables[len] = malloc(sizeof(variable_t));
    shell->variables[len]->name = strdup(name);
    if (value)
        shell->variables[len]->value = strdup(value);
    else
        shell->variables[len]->value = strdup("\0");
    shell->variables[len + 1] = NULL;
}

char *get_variable(shell_t *shell, char *name)
{
    for (int i = 0; shell->variables[i]; i++)
        if (my_strcmp(shell->variables[i]->name, name))
            return strdup(shell->variables[i]->value);
    return NULL;
}

void delete_variable(variable_t ***shell_variables, char *name)
{
    variable_t **variables = NULL;
    int index = 0;
    int k = 0;

    for (; (*shell_variables)[index]; index++)
        if (my_strcmp((*shell_variables)[index]->name, name))
            break;
    if (not (*shell_variables)[index])
        return;
    variables = malloc(sizeof(variable_t *) *
            variable_len(*shell_variables));
    for (int j = 0; (*shell_variables)[j]; j++) {
        if (j isnt index) {
            variables[k] = malloc(sizeof(variable_t));
            variables[k]->name = strdup((*shell_variables)[j]->name);
            variables[k]->value = strdup((*shell_variables)[j]->value);
            k++;
        }
    }
    variables[k] = NULL;
    *shell_variables = variables;
}
