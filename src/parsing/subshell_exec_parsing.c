/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** parsing subshell op
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include "command.h"
#include "shell.h"
#include "my.h"
#include "iterators.h"
#include "operator_abstract.h"
#include "read_line.h"
#include "env.h"
#include "parsing.h"
#include "execution.h"

int handle_special_char(char ***cmd, int i, int nb_opened, int spec_exec)
{
    if (my_strcmp((*cmd)[i], "(") and spec_exec is NONE) {
        delete_from_array(*cmd, i);
        return PARENTHESIS;
    }
    if (my_strcmp((*cmd)[i], ")") and nb_opened is 0) {
        delete_from_array(*cmd, i);
        return NONE;
    }
    return spec_exec;
}

int count_parenthesis(char *cmd, int nb_opened)
{
    if (my_strcmp(cmd, "("))
        nb_opened += 1;
    if (my_strcmp(cmd, ")"))
        nb_opened -= 1;
    return nb_opened;
}

cmd_list_t **get_special_exec_op(char **cmd, int spec_exec, int prev_exec)
{
    cmd_list_t **cmd_list = NULL;
    int nb_opened = 0;
    int ind_cmd = -1;

    for (int i = 0; cmd[i]; i++) {
        prev_exec = spec_exec;
        spec_exec = handle_special_char(&cmd, i, nb_opened, spec_exec);
        nb_opened = count_parenthesis(cmd[i], nb_opened);
        if (cmd[i] and (prev_exec != spec_exec or i == 0)) {
            ind_cmd += 1;
            cmd_list = realloc(cmd_list, sizeof(cmd_list_t *) * (ind_cmd + 2));
            cmd_list[ind_cmd + 1] = NULL;
            cmd_list[ind_cmd] = malloc(sizeof(cmd_list_t));
            cmd_list[ind_cmd]->cmd = NULL;
            cmd_list[ind_cmd]->execution = spec_exec;
        }
        cmd_list[ind_cmd]->cmd =
            concate(concate(cmd_list[ind_cmd]->cmd, cmd[i]), " ");
    }
    return cmd_list;
}

unparsed_cmd_t **get_cmds(char *lineptr)
{
    cmd_list_t **cmd_list = NULL;
    unparsed_cmd_t **cmds = NULL;
    char **cmd = parse_cmd(lineptr);

    cmd_list = get_special_exec_op(cmd, NONE, NONE);
    for (int i = 0; cmd_list and cmd_list[i]; i++)
        cmd_list[i]->cmd = clean_line(cmd_list[i]->cmd);
    cmds = get_spec_cond_exec_op(cmd_list);
    for (int i = 0; cmds and cmds[i]; i++)
        cmds[i]->cmd = clean_line(cmds[i]->cmd);
    return cmds;
}
