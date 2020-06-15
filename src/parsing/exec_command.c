/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** funcused to handle command line
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "iterators.h"
#include "job.h"
#include "my.h"
#include "command.h"
#include "operator_abstract.h"
#include "built_in.h"
#include "parsing.h"
#include "execution.h"
#include "shell.h"
#include "wordexp.h"

define_iter(command_t);

int exec_process(Iter(command_t) *commands, shell_t *shell);
void change_alias(char ***arg, char ***aliases);
bool is_there_alias(char **arg, char ***aliases);
bool is_alias_loop(char **arg, char ***aliases);

bool cmd_not_valid(char **command)
{
    for (int i = 0; command[i]; i++) {
        if (is_redirect(command[i]) and not command[i + 1]) {
            printf("Missing name for redirect\n");
            return true;
        } else if (is_pipe(command[i]) and (not command[i + 1] or i is 0)) {
            printf("Invalid null command.\n");
            return true;
        }
    }
    return false;
}

command_t *init_cmd_struct(char ***argv, char ***aliases, char *escape_char)
{
    command_t *command = malloc(sizeof(command_t));

    command->path = NULL;
    command->red_input_op = _;
    command->red_output_op = _;
    command->input_op_arg = NULL;
    command->output_op_arg = NULL;
    get_operator_and_arg(command, *argv);
    format_argv_for_execution(command, argv);
    if (replace_globbings(command) is MINOR_ERROR)
        return NULL;
    while (is_there_alias(command->argv, aliases)) {
        if (is_alias_loop(command->argv, aliases)) {
            write(2, "Alias loop.\n", 12);
            return NULL;
        }
        change_alias(&command->argv, aliases);
    }
    change_escape_char(&command->argv, escape_char);
    command->executable_name = command->argv[0];
    return command;
}

int exec_normal_process(char **parsed_cmd, shell_t *shell, char *escape_char)
{
    Iter(command_t) *commands = new_iter(command_t);
    command_t *command = NULL;

    while (parsed_cmd[0]) {
        command = init_cmd_struct(&parsed_cmd, shell->aliases, escape_char);
        if (not command)
            return MINOR_ERROR;
        push_to_end(commands, command);
    }
    return exec_process(commands, shell);
}

int exec_parenthised_process(unparsed_cmd_t *unparsed_cmd, shell_t *shell)
{
    int status = 0;
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        process_line(unparsed_cmd->cmd, shell);
        exit(my_getnbr(get_variable(shell, "?")));
    } else {
        wait(&status);
    }
    return status;
}

int exec_cmd(char **parsed_cmd, unparsed_cmd_t *unparsed_cmd,
            shell_t *shell, char *escape_char)
{
    if (cmd_not_valid(parsed_cmd))
        return MINOR_ERROR;
    if (unparsed_cmd->special_exec is PARENTHESIS) {
        return exec_parenthised_process(unparsed_cmd, shell);
    } else {
        return exec_normal_process(parsed_cmd, shell, escape_char);
    }
}
