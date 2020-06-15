/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** execution header
*/

#ifndef EXECUTION_H
#define EXECUTION_H
#include <stdlib.h>
#include <stdbool.h>
#include "command.h"
#include "shell.h"

int exec_cmd(char **parsed_cmd, unparsed_cmd_t *unparsed_cmd,
        shell_t *shell, char *escape_char);
void format_argv_for_execution(command_t *command, char ***argv);
bool search_path(command_t *cmd, shell_t *shell);
char *execute_backticks(char *cmdptr, shell_t *shell);
int exec_script(const char *file, shell_t *shell);
int exec_line(char *lineptr, shell_t *shell, char *escape_char);

#endif /* EXECUTION_H */
