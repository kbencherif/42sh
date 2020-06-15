/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** alias built_in
*/

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <wordexp.h>
#include <string.h>
#include "built_in.h"
#include "my.h"
#include "shell.h"
#include "env.h"
#include "operator_abstract.h"

int get_alias_index(char *str, char ***aliases);
void print_alias(char *cmd, char **alias, bool which_cmd);
char *get_variable(shell_t *shell, char *name);
int arraylen(char **arr);

void print_double_arr(char **arr)
{
    for (int i = 0; arr[i]; i++)
        printf("%s\n", arr[i]);
}

void create_arr(char ***arr, char *str)
{
    int arr_size = arraylen(*arr);
    char **new_arr = NULL;
    int i = 0;

    if (arr_size is 0) {
        *arr = malloc(sizeof(char *) * 2);
        (*arr)[0] = strdup(str);
        (*arr)[1] = NULL;
    }
    else {
        new_arr = malloc(sizeof(char *) * (arr_size + 2));
        for (; (*arr)[i]; i++)
            new_arr[i] = strdup((*arr)[i]);
        new_arr[i] = strdup(str);
        new_arr[i + 1] = NULL;
        *arr = new_arr;
    }
}

char **get_matching_cmd(char *path_env, char *cmd, char *path_var)
{
    char **parsed_path = my_str_to_word_array(path_env, ":");
    char **match_cmd = NULL;
    char *str = NULL;
    int i = 0;

    if (not parsed_path) {
        parsed_path = my_str_to_word_array(path_var, ":");
        if (not parsed_path)
            return NULL;
    }
    for (int i = 0; parsed_path[i]; i++) {
        str = concate(parsed_path[i], "/");
        str = concate(str, cmd);
        if (access(str, F_OK) isnt -1)
            create_arr(&match_cmd, str);
    }
    if (match_cmd) {
        i = arraylen(match_cmd);
        match_cmd[i] = NULL;
    }
    return match_cmd;
}

bool is_builtin(char *cmd)
{
    for (int i = 0; FUNC[i].name; i++) {
        if (my_strcmp(FUNC[i].name, cmd))
            return true;
    }
    return false;
}

int my_where(char **arg, void *shell_s)
{
    shell_t *shell = (shell_t *) shell_s;
    char **matching_str = NULL;
    int i = 0;

    if (!arg[0] or !arg) {
        write(2, "where: Too few arguments.\n", 26);
        return 1;
    }
    for (int j = 0; arg[j]; j++) {
        if ((i = get_alias_index(arg[j], shell->aliases)) >= 0)
            print_alias(arg[j], shell->aliases[i], false);
        if (is_builtin(arg[j]))
            printf("%s is a shell built-in\n", arg[j]);
        if ((matching_str = get_matching_cmd(
            my_getenv("PATH", shell->env), arg[j],
            get_variable(shell, "path"))))
            print_double_arr(matching_str);
        else if (not matching_str and i is -1)
            return 1;
    }
    return 0;
}
