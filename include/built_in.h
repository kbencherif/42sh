/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** builtin.h
*/

#ifndef BUILT_IN_H_
#define BUILT_IN_H_
#include <stdlib.h>
#include <stdbool.h>
#include "command.h"

bool isnt_builtin(command_t *command);
int cd_cmd(char **arg, void *env_list);
int my_env(char **arg, void *env_list);
int my_exit(char **arg, void *env_list);
int my_echo(char **arg, void *env_list);
int my_repeat(char **arg, void *shell_s);
int my_history(char **arg, void *env_list);
int my_unsetenv(char **field, void *env_list);
int my_setenv(char **arg, void *env_list);
int add_alias(char **arg, void *aliases_list);
int remove_alias(char **arg, void *aliases_list);
int my_set(char **arg, void *shell_s);
int my_unset(char **arg, void *shell_s);
int my_which(char **arg, void *shell);
int my_where(char **arg, void *shell);
void clean_cote(char *str);

typedef int (*built_in_cmd_t) (char **arg, void *env);

typedef struct builtin_tab {
    char *name;
    built_in_cmd_t builtin;
} builtin_tab_t;

static const builtin_tab_t FUNC[] = {
    {"cd", cd_cmd},
    {"exit", my_exit},
    {"unsetenv", my_unsetenv},
    {"setenv", my_setenv},
    {"env", my_env},
    {"history", my_history},
    {"echo", my_echo},
    {"alias", add_alias},
    {"unalias", remove_alias},
    {"set", my_set},
    {"unset", my_unset},
    {"which", my_which},
    {"where", my_where},
    {"repeat", my_repeat},
    {NULL, NULL}
};

#endif /* ifndef BUILT_IN_H_ */
