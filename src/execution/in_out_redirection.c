/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** in out red
*/

#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "command.h"
#include "operator_abstract.h"
#include "my.h"
#include "iterators_prototype.h"

define_prototype(command_t);

bool redirect_to_right_streams(command_t *cmd, int input_file_fd)
{
    int output_file_fd = 0;
    int flags = O_CREAT | O_WRONLY;

    if (cmd->red_input_op is RED_IN) {
        dup2(input_file_fd, STDIN_FILENO);
        close(input_file_fd);
    }
    if (cmd->red_output_op is RED_OUT
        or cmd->red_output_op is RED_OUT_A) {
        if (cmd->red_output_op is RED_OUT_A)
            flags = flags | O_APPEND;
        output_file_fd = open(cmd->output_op_arg, flags, 0644);
        if (output_file_fd is -1)
            return false;
        dup2(output_file_fd, STDOUT_FILENO);
        close(output_file_fd);
    }
    return true;
}

bool open_redirections_streams(int *input_file_fd, command_t *cmd)
{
    int flags = O_RDONLY;

    if (cmd->red_input_op is RED_IN) {
        *input_file_fd = open(cmd->input_op_arg, flags);
        if (*input_file_fd < 0) {
            printf("%s: No such file or directory.\n",
                cmd->input_op_arg);
            return false;
        }
    }
    return true;
}

void handle_stdin_redirection(Iter(command_t) *commands, filedes_t *filedes)
{
    if (commands->elem->data->red_input_op is RED_STDIN) {
        dup2(filedes->usr_input_pipe[0], 0);
        close(filedes->usr_input_pipe[1]);
    }
}

bool redirect_fildes(Iter(command_t) *commands, filedes_t *filedes, int i)
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
        for (int j = 0; j < 2 * (int) ((len(commands) - 1)); j++)
            close(filedes->pipes_fd[j]);
    }
    if (commands->elem->data->red_input_op is RED_STDIN)
        handle_stdin_redirection(commands, filedes);
    return true;
}

void init_pipes(Iter(command_t) *commands, int *pipe_fds, int *usr_input_pipe)
{
    for (int i = 0; i < (int) len(commands) - 1; i++)
        pipe(pipe_fds + i * 2);
    if (commands->elem->data->red_input_op is RED_STDIN)
        pipe(usr_input_pipe);
}
