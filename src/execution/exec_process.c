/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** exec process
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "execution.h"
#include "iterators.h"
#include "built_in.h"
#include "iterators_prototype.h"
#include "operator_abstract.h"
#include "command.h"
#include "errno.h"
#include "read_line.h"
#include "shell.h"
#include "my.h"
#include "env.h"

define_prototype(command_t);
define_prototype(char_ptr);

void init_pipes(Iter(command_t) *commands, int *pipe_fds, int *usr_input_pipe);
bool open_redirections_streams(int *input_file_fd, command_t *cmd);
bool redirect_to_right_streams(command_t *cmd, int input_file_fd);
bool redirect_fildes(Iter(command_t) *commands, filedes_t *filedes, int i);
void handle_stdin_redirection(Iter(command_t) *commands, filedes_t *filedes);
int exec_builtin(Iter(command_t) *commands, filedes_t *filedes,
                int j, shell_t *shell);
filedes_t *init_filedes(Iter(command_t) *commands);
void handle_child_signals(int status);

void fork_for_stdin_red(Iter(command_t) *commands, filedes_t *filedes,
        shell_t *shell)
{
    pid_t pid = fork();
    char *buf = NULL;
    Iter(char_ptr) *usr_input = new_iter(char_ptr);
    char **next = malloc(sizeof(char *));

    if (pid is 0) {
        close(filedes->usr_input_pipe[0]);
        while (read_line_stdin("? ", &buf, shell) and
            not my_strcmp(buf, commands->elem->data->input_op_arg)) {
            *next = concate(buf, "\n");
            push_to_end(usr_input, next);
            next = malloc(sizeof(char *));
        }
        while ((next = next(usr_input)))
            write(filedes->usr_input_pipe[1], *next, strlen(*next));
        exit(0);
    }
}

int handle_childs_exec(Iter(command_t) *commands, shell_t *shell,
                        filedes_t *filedes, int i)
{
    pid_t pid;
    command_t *cmd = commands->elem->data;

    pid = fork();
    if (pid is 0) {
        if (not redirect_fildes(commands, filedes, i))
            return MINOR_ERROR;
        execve(concate(cmd->path, cmd->executable_name),
            cmd->argv, shell->env);
        if (errno is ENOEXEC) {
            printf("%s: Exec format error. Wrong Architecture.\n",
                concate(cmd->path, cmd->executable_name));
            return MINOR_ERROR;
        }
        exit(0);
    }
    if (commands->elem->data->red_input_op is RED_STDIN)
        fork_for_stdin_red(commands, filedes, shell);
    return NO_ERROR;
}

int handle_parent_process(Iter(command_t) *commands,
                            int *pipe_fds,
                            int *usr_input_pipe,
                            int err)
{
    int status = 0;

    if (len(commands) > 1)
        for (int j = 0; j < (int) (2 * (len(commands) - 1)); j++)
            close(pipe_fds[j]);
    if (commands->elem and commands->elem->data->red_input_op is RED_STDIN) {
        close(usr_input_pipe[0]);
        close(usr_input_pipe[1]);
        wait(&status);
    }
    for (int j = 0; j < (int) len(commands); j++)
        wait(&status);
    if (WIFSIGNALED(status))
        handle_child_signals(status);
    if (err)
        return err;
    else
        return status % 255;
}

int execute_child_process(Iter(command_t) *commands,
                    shell_t *shell,
                    filedes_t *filedes,
                    int i)
{
    if (commands->elem->data->red_input_op and
        not open_redirections_streams(
        &filedes->input_file_fd, commands->elem->data))
        return MINOR_ERROR;
    if (not isnt_builtin(commands->elem->data)) {
        if (exec_builtin(commands, filedes, i, shell) is MINOR_ERROR)
            return MINOR_ERROR;
    } else if (search_path(commands->elem->data, shell)) {
        if (handle_childs_exec(commands, shell, filedes, i) is MINOR_ERROR)
            return MINOR_ERROR;
    } else {
        return MINOR_ERROR;
    }
    return NO_ERROR;
}

int exec_process(Iter(command_t) *commands, shell_t *shell)
{
    filedes_t *filedes = init_filedes(commands);
    int pipe_fds[(len(commands) - 1) * 2];
    int usr_input_pipe[2];
    int err = 0;

    filedes->pipes_fd = pipe_fds;
    filedes->usr_input_pipe = usr_input_pipe;
    if (len(commands) > 1 or commands->elem->data->red_input_op is RED_STDIN)
        init_pipes(commands, filedes->pipes_fd, filedes->usr_input_pipe);
    for (int i = 0; commands->elem; i++) {
        err = execute_child_process(commands, shell, filedes, i);
        next(commands);
    }
    return handle_parent_process(commands,
                        filedes->pipes_fd,
                        filedes->usr_input_pipe,
                        err);
}
