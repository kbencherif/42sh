/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** parenthesis error handling
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

bool too_many_parenthesis(char *line)
{
    int nb_opened = 0;
    int nb_closed = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '(')
            nb_opened += 1;
        else if (line[i] == ')')
            nb_closed += 1;
        if (nb_closed > nb_opened) {
            printf("Too many )'s.\n");
            return true;
        }
    }
    if (nb_opened > nb_closed) {
        printf("Too many ('s.\n");
        return true;
    }
    return false;
}

bool is_special_string(char *str)
{
    return my_strcmp(str, ";") ||
        my_strcmp(str, "&&") ||
        my_strcmp(str, "||") ||
        my_strcmp(str, "|") ||
        my_strcmp(str, ")") ||
        my_strcmp(str, "(");
}

bool badly_placed_parenthesis(char *line)
{
    char **parsed_cmd = parse_cmd(line);

    for (int i = 0; parsed_cmd[i]; i++) {
        if (my_strcmp(parsed_cmd[i], "(") and i > 0 and
            not is_special_string(parsed_cmd[i - 1])) {
            printf("Badly placed ()'s.\n");
            return true;
        } if (my_strcmp(parsed_cmd[i], ")") and parsed_cmd[i + 1] and
            not is_special_string(parsed_cmd[i + 1])) {
            printf("Badly placed ()'s.\n");
            return true;
        }
    }
    return false;
}

bool line_valid(char *line)
{
    if (isnt_valid_typed_line(line))
        return false;
    if (backtick_unmatched(line))
        return false;
    if (too_many_parenthesis(line) or badly_placed_parenthesis(line))
        return false;
    return true;
}
