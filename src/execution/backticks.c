/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** backtick exec and replacement
*/

#include "command.h"
#include "my.h"
#include "parsing.h"
#include "read_line.h"
#include "shell.h"
#include "execution.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

char *insert_str(char *cmdptr, char *output, int i)
{
    char *new_str = calloc(1, strlen(cmdptr) + strlen(output) + 1);

    strncpy(new_str, cmdptr, i);
    strcat(new_str, output);
    strcat(new_str, cmdptr + i);
    return new_str;
}

char *replace_by_output(int *fds, char *cmdptr)
{
    char *buffer = NULL;
    char *output = NULL;
    size_t i = 0;
    FILE *output_file = fdopen(fds[0], "r");

    close(fds[1]);
    while (getline(&buffer, &i, output_file) != -1) {
        buffer[strlen(buffer) - 1] = 0;
        output = concate(output, concate(buffer, " "));
    }
    close(fds[0]);
    fclose(output_file);
    i = find_char(cmdptr, '`');
    cmdptr = delete_backticked_cmd(cmdptr);
    if (!output)
        return cmdptr;
    cmdptr = insert_str(cmdptr, output, i);
    return cmdptr;
}

char *replace_backticked_cmd(char **backticked_cmd,
                            char *cmdptr, shell_t *shell)
{
    int status = 0;
    int fds[2];
    pid_t pid;

    for (int i = 0; backticked_cmd[i]; i++) {
        pipe(fds);
        pid = fork();
        if (pid == 0) {
            dup2(fds[1], STDOUT_FILENO);
            process_line(backticked_cmd[i], shell);
            close(fds[1]);
            close(fds[0]);
            exit(my_getnbr(get_variable(shell, "?")));
        } else {
            wait(&status);
            cmdptr = replace_by_output(fds, cmdptr);
        }
    }
    return cmdptr;
}

char *execute_backticks(char *cmdptr, shell_t *shell)
{
    char **backticked_cmd = NULL;

    backticked_cmd = get_backticked_cmd(cmdptr);
    if (!*backticked_cmd)
        return cmdptr;
    cmdptr = replace_backticked_cmd(backticked_cmd, cmdptr, shell);
    return cmdptr;
}
