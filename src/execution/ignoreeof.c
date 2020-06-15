/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** main file
*/

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include "shell.h"
#include "my.h"
#include "operator_abstract.h"

bool does_exist(variable_t **variables, char *name);

bool check_value(int value, shell_t *shell)
{
    if (shell->eof_nb >= value)
        return false;
    return true;
}

bool manage_eof(shell_t *shell)
{
    char *ieof_value = get_variable(shell, "ignoreeof");

    if (ieof_value) {
        printf("\nUse \"exit\" to the shell.\n");
        shell->eof_nb++;
        if (my_strcmp("", ieof_value))
            return true;
        else
            return check_value(my_getnbr(ieof_value), shell);
    }
    return false;
}
