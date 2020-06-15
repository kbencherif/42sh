/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** && || ; oop parsing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "command.h"
#include "iterators_prototype.h"
#include "shell.h"
#include "my.h"
#include "operator_abstract.h"
#include "parsing.h"

static int get_line_last_op(char *line)
{
    char *op_tab[] = {";", "||", "&&", NULL};
    int op_len = 0;

    for (int i = 0; op_tab[i]; i++) {
        op_len = strlen(op_tab[i]);
        if ((int) strlen(line) > op_len
            and my_strncmp(line + strlen(line) - op_len, op_tab[i], op_len))
            return i;
    }
    return NONE;
}

static unparsed_cmd_t **add_subshell_command(unparsed_cmd_t **cmds,
                                        cmd_list_t **cmd_list,
                                        int i, int *j)
{
    int len = 0;

    for (; cmds and cmds[len]; len++);
    cmds = realloc(cmds, sizeof(unparsed_cmd_t *) * (len + 2));
    cmds[*j] = malloc(sizeof(unparsed_cmd_t));
    cmds[*j]->cmd = strdup(cmd_list[i]->cmd);
    cmds[*j]->special_exec = cmd_list[i]->execution;
    if (i > 0)
        cmds[*j]->condition_exec = get_line_last_op(cmd_list[i - 1]->cmd);
    else
        cmds[*j]->condition_exec = NONE;
    (*j)++;
    cmds[len + 1] = NULL;
    return cmds;
}

unparsed_cmd_t **get_spec_cond_exec_op(cmd_list_t **cmd_list)
{
    unparsed_cmd_t **cmds = NULL;
    int j = 0;

    for (int i = 0; cmd_list and cmd_list[i]; i++) {
        if (cmd_list[i]->execution isnt NONE)
            cmds = add_subshell_command(cmds, cmd_list, i, &j);
        else
            cmds = get_chained_commands(cmds, cmd_list[i]->cmd,
                cmd_list[i]->execution, &j);
    }
    return cmds;
}

static unparsed_cmd_t *get_next_cmd(unparsed_cmd_t *cmd, char **cmd_line,
                                    int exec)
{
    char *operator_tab[] = {";", "||", "&&"};

    cmd = malloc(sizeof(unparsed_cmd_t));
    cmd->condition_exec = NONE;
    for (int j = 0; j < 3; j++) {
        if (my_strncmp(*cmd_line,
                        operator_tab[j],
                        strlen(operator_tab[j]))) {
            cmd->condition_exec = j;
            *cmd_line += strlen(operator_tab[j]);
        }
    }
    if (is_empty_command(cmd_line))
        return NULL;
    cmd->cmd = strndup(*cmd_line, find_next_op(*cmd_line));
    cmd->special_exec = exec;
    *cmd_line += find_next_op(*cmd_line);
    return cmd;
}

unparsed_cmd_t **get_chained_commands(unparsed_cmd_t **commands,
                                        char *cmd_part, int exec,
                                        int *j)
{
    int nb_op = count_operators(cmd_part);
    int len = 0;

    for (; commands and commands[len]; len++);
    commands = realloc(commands, sizeof(unparsed_cmd_t *) * (len + nb_op + 2));
    commands[len + nb_op + 1] = NULL;
    for (int i = 0; i isnt nb_op + 1; i++) {
        if ((commands[*j] = get_next_cmd(commands[*j], &cmd_part, exec)))
            (*j)++;
        commands[*j] = NULL;
    }
    return commands;
}
