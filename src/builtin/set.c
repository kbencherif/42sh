/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** set builtin
*/

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "shell.h"
#include "operator_abstract.h"
#include "my.h"

char **my_str_to_word_array(char *str, char *delim);
void delete_variable(variable_t ***shell_variables, char *name);
int arraylen(char **array);
int is_alpha(char c);

void print_variables(variable_t **variables)
{
    for (int i = 0; variables[i]; i++)
        printf("%s %s\n", variables[i]->name, variables[i]->value);
}

bool is_valid(char **arg)
{
    for (int i = 0, j = 0; arg[i]; i++) {
        for (j = 0; arg[i][j] and arg[i][j] isnt '='; j++);
        if (arg[i][j] and not arg[i][j + 1])
            return true;
    }
    return false;
}

int modify_variable(char **arg, shell_t *shell, bool original_arg)
{
    for (int i = 0; arg[i]; i++) {
        if (not my_strcmp(arg[i], "=") and not is_alpha(arg[i][0])) {
            write(2, "set: Variable name must begin with a letter.\n", 45);
            return 1;
        }
        if (arg[i + 1] and my_strcmp(arg[i + 1], "=") and arg[i + 2]) {
            add_variable(shell, arg[i], arg[i + 2]);
            i += 2;
        }
        else if (not original_arg) {
            add_variable(shell, arg[i], arg[i + 1]);
            i++;
        }
        else if (not my_strcmp(arg[i], "="))
            add_variable(shell, arg[i], NULL);
    }
    return 0;
}

int my_set(char **arg, void *shell_s)
{
    char **new_arg = NULL;
    shell_t *shell = (shell_t *) shell_s;
    int status = 0;

    if (not arg[0]) {
        print_variables(shell->variables);
        return 0;
    }
    if (arraylen(arg) is 1) {
        new_arg = my_str_to_word_array(arg[0], "=");
        status = modify_variable(new_arg, shell, false);
    }
    else
        status = modify_variable(arg, shell, true);
    return status;
}

int my_unset(char **arg, void *shell_s)
{
    shell_t *shell = (shell_t *) shell_s;

    if (not arg[0]) {
        write(2, "unset: Too few arguments.\n", 26);
        return 1;
    }
    for (int i = 0; arg[i]; i++)
        delete_variable(&shell->variables, arg[i]);
    return 0;
}
