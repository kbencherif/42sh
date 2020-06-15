/*
** EPITECH PROJECT, 2019
** minishell
** File description:
** parsed_command.c
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "parsing.h"
#include "operator_abstract.h"

char *get_quote(char *str, int *i);
void is_quote(char c, bool *in_quote);

int is_special_char(char c)
{
        return c == ';' || c == ' ' || c == '<' || c == '>'
            || c == '|' || c == '`' || c == '(' || c == ')';
}

int get_nb_words(char *cmd)
{
    int nb_words = 1;

    for (int i = 0; cmd[i]; i++)
        if (cmd[i] == ';' || cmd[i] == '<' || cmd[i] == '>'
            || cmd[i] == '|' || cmd[i] == '`' || cmd[i] == '('
            || cmd[i] == ')')
            nb_words += 2;
        else if (cmd[i] == ' ')
            nb_words += 1;
    return nb_words;
}

char *special_op(char *cmd, int *i)
{
    char *word = NULL;

    if (is_special_char(cmd[*i])) {
        word = malloc(2);
        word[0] = cmd[*i];
        word[1] = 0;
    }
    return word;
}

char *parse_word(char *cmd, int *i)
{
    char *word = NULL;
    int j = 0;
    int w_len = 0;
    bool in_quote = false;

    if ((word = special_op(cmd, i)))
        return word;
    for (; (!is_special_char(cmd[*i + w_len]) || in_quote)
            && cmd[*i + w_len]; w_len++)
        is_quote(cmd[*i + w_len], &in_quote);
    word = malloc(w_len + 1);
    while (w_len--) {
        word[j++] = cmd[*i];
        is_quote(cmd[*i], &in_quote);
        *i += 1;
    }
    word[j] = 0;
    if (is_special_char(cmd[*i]))
        *i -= 1;
    return word;
}

char **parse_cmd(char *cmd)
{
    char **parsed_cmd = NULL;
    int j = 0;

    cmd = clean_line(cmd);
    parsed_cmd = malloc(sizeof(char *) * (get_nb_words(cmd) + 1));
    for (int i = 0; i < (int) strlen(cmd); i++)
        parsed_cmd[j] = get_word(cmd, &i, &j);
    parsed_cmd[j] = NULL;
    parsed_cmd = concate_double_operators(parsed_cmd);
    return parsed_cmd;
}
