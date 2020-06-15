/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** main file
*/

#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "env.h"

void post_cmd_actions(shell_t *shell, int cmd_status)
{
    add_variable(shell, "?", my_itoa(cmd_status));
    add_variable(shell, "status", my_itoa(cmd_status));
    add_variable(shell, "owd", my_getenv("OLD_PWD", shell->env));
    add_variable(shell, "cwd", getcwd(NULL, 0));
}
