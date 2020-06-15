/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** globbings handling
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "iterators.h"
#include "job.h"
#include "my.h"
#include "command.h"
#include "operator_abstract.h"
#include "parsing.h"
#include "shell.h"
#include "wordexp.h"

int array_len(char **array)
{
    int len = 0;

    for (; array[len]; len++);
    return len;
}

void insert_matched_pattern_to_argv(command_t *command,
                                    wordexp_t wordp,
                                    int *i)
{
    char **matched_words = wordp.we_wordv;
    int base_argv_len = array_len(command->argv);
    int new_size = base_argv_len + wordp.we_wordc - 1;

    command->argv = realloc(command->argv, sizeof(char *) * (new_size + 1));
    for (int j = *i; command->argv[j]; j++)
        command->argv[j + wordp.we_wordc - 1] = strdup(command->argv[j]);
    for (int j = 0; matched_words[j] and j < (int) wordp.we_wordc; j++)
        command->argv[(*i)++] = strdup(matched_words[j]);
    if (base_argv_len < *i)
        command->argv[*i] = NULL;
}

bool string_contain_globbing(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] is '*' or str[i] is '?')
            return true;
        if (str[i] is '[' and find_char(str, ']') >= 0
            and find_char(str, ']') > i + 1)
            return true;
    }
    return false;
}

bool doesnt_contains_globbing(char **argv)
{
    for (int j = 0; argv[j]; j++) {
        if (string_contain_globbing(argv[j]))
            return false;
    }
    return true;
}

int replace_globbings(command_t *command)
{
    wordexp_t wordp;

    if (doesnt_contains_globbing(command->argv))
        return NO_ERROR;
    for (int i = 0; command->argv[i];) {
        wordexp(command->argv[i], &wordp, 0);
        if (not my_strcmp(*wordp.we_wordv, command->argv[i]))
            insert_matched_pattern_to_argv(command, wordp, &i);
        else if (string_contain_globbing(*wordp.we_wordv)) {
            printf("%s: No match.\n", command->argv[0]);
            return MINOR_ERROR;
        } else
            i++;
    }
    return NO_ERROR;
}
