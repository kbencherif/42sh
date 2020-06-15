/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** env builtin func
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "built_in.h"
#include "my.h"
#include "env.h"
#include "shell.h"

int my_unsetenv(char **arg, void *env_list)
{
    char ***env = (char ***) env_list;
    int replace = 0;
    int i = 0;
    char *field_name = NULL;

    if (!*arg) {
        write(2, "unsetenv: Too few arguments.\n", 30);
        return MINOR_ERROR;
    }
    for (; (*env)[i]; i++) {
        field_name = get_field_name(strdup((*env)[i]));
        if ((my_strcmp(field_name, *arg)) || replace) {
            (*env)[i] = (*env)[i + 1];
            replace = 1;
        }
    }
    (*env)[i] = NULL;
    return NO_ERROR;
}

int isnt_valid(char *to_set, void *env_list)
{
    char ***env = (char ***) env_list;
    if (!to_set) {
        my_env(NULL, env);
        return 1;
    }
    if (!((to_set[0] >= 'A' && to_set[0] <= 'Z') ||
            (to_set[0] >= 'a' && to_set[0] <= 'z'))) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return 1;
    }
    for (int i = 0; to_set[i]; i++) {
        if ((!is_alphanumeric(to_set[i])) &&
            to_set[i] != '_') {
            write(2,
                "setenv: Variable name must contain alphanumeric characters.\n"
                , 60);
            return 1;
        }
    }
    return 0;
}

int my_setenv(char **arg, void *env_list)
{
    char ***env = (char ***) env_list;
    int i = 0;
    int j = 0;
    char **new_env = NULL;

    if (arg[0] && arg[1] && arg[1][0] == '"'
            && arg[1][strlen(arg[1]) - 1] == '"')
        clean_cote(arg[1]);
    if (isnt_valid(arg[0], env))
        return MINOR_ERROR;
    replace_existing_field(arg[0], env, &i);
    new_env = malloc(sizeof(char *) * (i + 2));
    for (; (*env)[j]; j++)
        new_env[j] = strdup((*env)[j]);
    arg[0] = concate(arg[0], "=");
    arg[0] = concate(arg[0], arg[1]);
    new_env[j] = strdup(arg[0]);
    new_env[j + 1] = NULL;
    *env = new_env;
    return NO_ERROR;
}

int my_echo(char **arg, UNUSED void *env)
{
    int i = 0;

    if (my_strcmp(arg[0], "-n"))
        i += 1;
    for (; arg[i]; i++) {
        printf("%s", arg[i]);
        if (arg[i + 1])
            printf(" ");
    }
    if (!my_strcmp(arg[0], "-n"))
        printf("\n");
    return NO_ERROR;
}

int my_env(UNUSED char **str, void *env_list)
{
    char ***env = (char ***) env_list;
    for (int i = 0; (*env)[i]; i++)
        printf("%s\n", (*env)[i]);
    return NO_ERROR;
}
