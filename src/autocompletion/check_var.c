/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** check_var
*/

#include "shell.h"
#include "utils.h"
#include "my.h"
#include <stddef.h>
#include <string.h>
#include "check_var.h"

char **check_var(char *to_autocomplete, shell_t *shell)
{
    char **env_match = get_env_match(to_autocomplete, shell->env);
    char **shell_var_match = get_shell_match(to_autocomplete, shell->variables);

    if ((env_match && shell_var_match) || (!env_match && !shell_var_match))
        return NULL;
    if (!env_match && arraylen(shell_var_match) == 1)
        return shell_var_match;
    if (!shell_var_match && arraylen(env_match) == 1)
        return env_match;
    return NULL;
}

char **get_env_match(char *to_autocomplete, char **env)
{
    char *match = NULL;
    int len = strlen(to_autocomplete);
    int match_len = 0;

    for (int i = 0; env[i]; i++) {
        if (!strncmp(to_autocomplete, env[i], len)) {
            match = match ? concate(match, env[i]) :
                strndup(env[i], find_char(env[i], '='));
            match_len = strlen(match);
            match = realloc(match, match_len + 2);
            match[match_len] = ':';
            match[match_len + 1] = '\0';
        }
    }
    return my_str_to_word_array(match, ":");
}

char **get_shell_match(char *to_autocomplete, variable_t **variables)
{
    char *match = NULL;
    int len = strlen(to_autocomplete);
    int match_len = 0;

    for (int i = 0; variables[i]; i++) {
        if (!strncmp(to_autocomplete, variables[i]->name, len)) {
            match = match ? concate(match, variables[i]->name) :
                strdup(variables[i]->name);
            match_len = strlen(match);
            match = realloc(match, match_len + 2);
            match[match_len] = ':';
            match[match_len + 1] = '\0';
        }
    }
    return my_str_to_word_array(match, ":");
}
