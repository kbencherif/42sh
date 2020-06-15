/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** check_var
*/


#ifndef __CHECK_VAR__
#define __CHECK_VAR__

#include "shell.h"

char **get_env_match(char *to_autocomplete, char **env);
char **get_shell_match(char *to_autocomplete, variable_t **variables);

#endif
