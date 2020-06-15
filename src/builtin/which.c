/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** alias built_in
*/

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "shell.h"
#include "env.h"
#include "operator_abstract.h"
#include "my.h"

int get_alias_index(char *str, char ***aliases);
bool is_builtin(char *cmd);
void create_arr(char ***arr, char *str);

void print_alias(char *cmd, char **alias, bool which_cmd)
{
    if (which_cmd)
        printf("%s:\taliased to", cmd);
    else
        printf("%s is aliased to", cmd);
    for (int i = 1; alias[i]; i++)
        printf(" %s", alias[i]);
    printf("\n");
}

char *get_first_matching_path(char *cmd, char *path_env, char *path_var)
{
    char **parsed_path = my_str_to_word_array(path_env, ":");
    char *str = NULL;

    if (not parsed_path) {
        parsed_path = my_str_to_word_array(path_var, ":");
        if (not parsed_path)
            return NULL;
    }
    for (int i = 0; parsed_path[i]; i++) {
        str = concate(parsed_path[i], "/");
        str = concate(str, cmd);
        if (access(str, F_OK) isnt -1) {
            return str;
        }
    }
    return NULL;
}

void manage_error(char *str, shell_t *shell, char *arg, int *ret)
{
    if ((str = get_first_matching_path(arg,
                    my_getenv("PATH", shell->env),
                    get_variable(shell, "path"))))
        printf("%s\n", str);
    else {
        printf("%s: Command not found.\n", arg);
        *ret = 1;
    }
}

int my_which(char **arg, void *shell_s)
{
    shell_t *shell = (shell_t *) shell_s;
    char *str = NULL;
    int i = 0;
    int ret = 0;

    if (!arg[0] or !arg) {
        write(2, "which: Too few arguments.\n", 26);
        return 1;
    }
    for (int j = 0; arg[j]; j++) {
        if ((i = get_alias_index(arg[j], shell->aliases)) >= 0)
            print_alias(arg[j], shell->aliases[i], true);
        else if (is_builtin(arg[j]))
            printf("%s: shell built-in command.\n", arg[j]);
        else
            manage_error(str, shell, arg[j], &ret);
    }
    return ret;
}
