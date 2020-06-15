/*
** EPITECH PROJECT, 2019
** minishell
** File description:
** parsed_command.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *parse_word(char *cmd, int *i);

char *get_word(char *cmd, int *i, int *j)
{
    char *word = NULL;

    if (cmd[*i] != ' ') {
        *j += 1;
        word = parse_word(cmd, i);
    }
    return word;
}
