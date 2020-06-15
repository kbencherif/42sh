/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** env utils func
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "env.h"
#include "built_in.h"

void clean_cote(char *str)
{
    str[strlen(str) - 1] = 0;
    for (int i = 0; str[i]; i++)
        str[i] = str[i + 1];
}

char **save_env(char **env)
{
    char **env_buf = NULL;
    int len = 0;

    for (; env[len]; len++);
    env_buf = malloc(sizeof(char *) * (len + 1));
    env_buf[len] = NULL;
    for (int i = 0; env[i]; i++)
        env_buf[i] = strdup(env[i]);
    return env_buf;
}

void replace_existing_field(char *to_set, char ***env, int *i)
{
    char *field_name = NULL;

    for (; (*env)[*i]; (*i)++) {
        field_name = get_field_name(strdup((*env)[*i]));
        if (my_strcmp(field_name, to_set))
            my_unsetenv(&to_set, env);
    }
}

char *get_field_name(char *field)
{
    int i = 0;

    for (; field[i] != '='; i++);
    field[i] = '\0';
    return field;
}

char *my_getenv(char *field, char **env)
{
    if (!field)
        return NULL;
    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], field, strlen(field))) {
            return my_strstr(env[i], field) + strlen(field) + 1;
        }
    }
    return NULL;
}
