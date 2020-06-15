/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** backticks
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

bool backtick_unmatched(char *command)
{
    int nb_backtick = 0;

    for (int i = 0; command[i]; i++) {
        if (command[i] == '`')
            nb_backtick++;
    }
    if (nb_backtick % 2 != 0) {
        printf("Unmatched '`'.\n");
        return true;
    }
    return false;
}

char **get_backticked_cmd(char *line)
{
    int nb_backtick = 0;
    char **backticked_cmd = NULL;

    for (int i = 0; line[i]; i++)
        if (line[i] == '`')
            nb_backtick++;
    backticked_cmd = malloc(sizeof(char *) * (nb_backtick / 2 + 1));
    backticked_cmd[nb_backtick / 2] = NULL;
    for (int i = 0; find_char(line, '`') >= 0; i++) {
        line += find_char(line, '`') + 1;
        backticked_cmd[i] = strndup(line, find_char(line, '`'));
        line += find_char(line, '`') + 1;
    }
    return backticked_cmd;
}

char *delete_backticked_cmd(char *line)
{
    int i = find_char(line, '`');

    for (int j = i; line[j]; j++)
        line[j] = line[j + 1];
    while (line[i] != '`')
        for (int j = i; line[j]; j++)
            line[j] = line[j + 1];
    for (int j = i; line[j]; j++)
        line[j] = line[j + 1];
    return line;
}
