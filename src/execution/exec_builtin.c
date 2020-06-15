/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** exec builtin
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "built_in.h"
#include "iterators_prototype.h"
#include "operator_abstract.h"
#include "command.h"
#include "errno.h"
#include "my.h"
#include "shell.h"

define_prototype(command_t);

bool redirect_to_right_streams(command_t *cmd, int input_file_fd);
void handle_stdin_redirection(Iter(command_t) *commands, filedes_t *filedes);
void special_aliases(shell_t *shell, char *escape_char, char *alias);

bool redirect_buildin_fildes(Iter(command_t) *commands,
        filedes_t *filedes, int i)
{
    if ((commands->elem->data->red_input_op
            or commands->elem->data->red_output_op) and
            not redirect_to_right_streams(commands->elem->data,
            filedes->input_file_fd))
        return false;
    if (len(commands) > 1) {
        if (commands->elem->next)
            dup2(filedes->pipes_fd[i * 2 + 1], STDOUT_FILENO);
        if (i isnt 0)
            dup2(filedes->pipes_fd[(i - 1) * 2], STDIN_FILENO);
    }
    if (commands->elem->data->red_input_op is RED_STDIN)
        handle_stdin_redirection(commands, filedes);
    return true;
}

int manage_builtin(shell_t *shell, int i, command_t *command, bool *executed)
{
    int ret = 0;

    if (my_strcmp(FUNC[i].name, command->executable_name) and
            (my_strcmp(command->executable_name, "alias") or
            my_strcmp(command->executable_name, "unalias"))) {
        *executed = true;
        return FUNC[i].builtin(command->argv + 1, &shell->aliases);
    } if (my_strcmp(FUNC[i].name, command->executable_name) and
            (my_strcmp(command->executable_name, "set") or
            my_strcmp(command->executable_name, "unset") or
            my_strcmp(command->executable_name, "which") or
            my_strcmp(command->executable_name, "where") or
            my_strcmp(command->executable_name, "repeat"))) {
        *executed = true;
        return FUNC[i].builtin(command->argv + 1, shell);
    } if (my_strcmp(FUNC[i].name, command->executable_name)) {
        ret = FUNC[i].builtin(command->argv + 1, &shell->env);
        if (my_strcmp(FUNC[i].name, "cd"))
            special_aliases(shell, NULL, "cwdcmd");
        *executed = true;
    }
    return ret;
}

int exec_builtin(Iter(command_t) *commands, filedes_t *filedes,
        int j, shell_t *shell)
{
    command_t *command = commands->elem->data;
    int save_stdin = dup(0);
    int save_stdout = dup(1);
    int err = 0;
    bool executed = false;

    if (my_strcmp("exit", commands->elem->data->executable_name)
            and commands->len > 1)
        return NO_ERROR;
    if (!redirect_buildin_fildes(commands, filedes, j))
        return MINOR_ERROR;
    for (int i = 0; FUNC[i].name and not executed; i++)
        err = manage_builtin(shell, i, command, &executed);
    dup2(save_stdin, STDIN_FILENO);
    dup2(save_stdout, STDOUT_FILENO);
    return err;
}
