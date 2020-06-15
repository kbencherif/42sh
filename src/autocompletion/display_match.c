/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** display_match
*/


#include "read_line.h"
#include <string.h>

void display_match(char **match, char *prompt, edit_line_t *line, char *to_find)
{
    int len = 0;
    char *last_index = rindex(to_find, '/');

    if (!match[0])
        return;
    to_find = last_index ? last_index + 1 : to_find;
    len = strlen(to_find);
    for (int j = 0; is_valid_character(match[0][j]); j++)
        if (j >= len || match[0][j] != to_find[j])
            insert_character_term(prompt, line, match[0][j]);
}
