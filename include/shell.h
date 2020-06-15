/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** shell data
*/

#ifndef SHELL_H
#define SHELL_H
#include "job.h"

typedef struct shell_variable {
    char *name;
    char *value;
} variable_t;

typedef struct shell {
    variable_t **variables;
    char **env;
    char ***aliases;
    job_t **jobs;
    int eof_nb;
} shell_t;

#define NO_ERROR 0
#define MINOR_ERROR 1
#define MAJOR_ERROR 2

void add_variable(shell_t *shell, char *name, char *value);
char *get_variable(shell_t *shell, char *name);
shell_t *init_shell(char **env);
char *get_variable_string(char *str);
char *replace_variable(char *variable_value, char *str);

#endif /* SHELL_H */
