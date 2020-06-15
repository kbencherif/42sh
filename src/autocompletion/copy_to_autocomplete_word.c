/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** copy_to_autocomplete_word
*/

#include "read_line.h"
#include <string.h>
#include "to_autocomplete.h"

char *copy_to_autocomplete_word(edit_line_t *line)
{
    char *to_autocomplet = strdup(line->line);
    int pos = line->cursor_pos->x;

    to_autocomplet[pos] = '\0';
    for ( ; pos && !is_sep(line->line[pos - 1]); pos--);
    to_autocomplet = is_sep(line->line[pos]) ? strdup(to_autocomplet) :
        strdup(to_autocomplet + pos);
    return to_autocomplet;
}

bool is_sep(char c)
{
    if (c == ';' || c == '|' || c == '&' || c == ' ' || c == '<' || c == '>')
        return true;
    return false;
}
