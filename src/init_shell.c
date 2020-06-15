/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** init_shell.c
*/

#include <stdlib.h>
#include "env.h"
#include "shell.h"

char ***add_special_aliases(void);

shell_t *init_shell(char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    shell->variables = NULL;
    shell->env = save_env(env);
    shell->aliases = NULL;
    shell->eof_nb = 0;
    add_variable(shell, "home", my_getenv("HOME", shell->env));
    add_variable(shell, "cwd", my_getenv("PWD", shell->env));
    add_variable(shell, "owd", " ");
    add_variable(shell, "path", my_getenv("PATH", shell->env));
    add_variable(shell, "shlvl", my_getenv("SHLVL", shell->env));
    add_variable(shell, "shell", my_getenv("SHELL", shell->env));
    add_variable(shell, "term", my_getenv("TERM", shell->env));
    add_variable(shell, "?", "0");
    add_variable(shell, "status", "0");
    return shell;
}
