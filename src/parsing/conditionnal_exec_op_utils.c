/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** conditionnal exec operators utils
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "command.h"
#include "iterators_prototype.h"
#include "shell.h"
#include "my.h"
#include "parsing.h"
#include "operator_abstract.h"

int count_operators(char *line)
{
    int nb_op = 0;

    for (; *line; line++)
        if (my_strncmp(line, "&&", 2)
            or my_strncmp(line, "||", 2)
            or my_strncmp(line, ";", 1))
            nb_op++;
    return nb_op;
}

int find_next_op(char *str)
{
    char *operator_tab[] = {";", "||", "&&"};
    int next_op_index = strlen(str);

    for (int i = 0; i < 3; i++) {
        if (find_str(str, operator_tab[i]) < next_op_index
            and find_str(str, operator_tab[i]) >= 0)
            next_op_index = find_str(str, operator_tab[i]);
    }
    return next_op_index;
}

bool is_empty_command(char **cmd_line)
{
    int next_char = 0;

    for (; (*cmd_line)[next_char]
        and (*cmd_line)[next_char] is ' '; next_char++);
    if (find_next_op(*cmd_line) is next_char) {
        *cmd_line += next_char;
        return true;
    } else {
        return false;
    }
}

bool isnt_valid_typed_line(char *line)
{
    if (strlen(line) > 1 and
        (my_strncmp(line + strlen(line) - 2, "||", 2) or
        my_strncmp(line + strlen(line) - 2, "&&", 2))) {
        printf("Invalid null command.\n");
        return true;
    }
    return false;
}
