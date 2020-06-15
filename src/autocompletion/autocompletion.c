/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** autocompletion
*/

#include "autocompletion.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>

void autocompletion(char *prompt, edit_line_t *line, shell_t *shell)
{
    char *to_autocomplete = NULL;
    char **match = NULL;

    if (!line->line[0])
        return;
    if (!(to_autocomplete = copy_to_autocomplete_word(line))[0])
        return;
    if (to_autocomplete[0] == '$') {
        if ((match = check_var(to_autocomplete, shell)))
            display_match(match, prompt, line, to_autocomplete + 1);
    } else if ((match = check_builtin_match(to_autocomplete))) {
        display_match(match, prompt, line, to_autocomplete);
    } else {
        add_star(&to_autocomplete);
        if (((match = check_other_possibilities(to_autocomplete, shell)) &&
                    arraylen(match) == 1) || matched_multiples_times(match)) {
            to_autocomplete[strlen(to_autocomplete) - 1] = '\0';
            display_match(match, prompt, line, to_autocomplete);
        }
    }
}

bool matched_multiples_times(char **to_check)
{
    if (!to_check || !to_check[0])
        return false;
    for (int i = 0; to_check[i]; i++) {
        if (i != 0 && strcmp(to_check[i], to_check[0]))
            return false;
    }
    return true;
}

void add_star(char **to_autocomplete)
{
    int len = strlen(*to_autocomplete);

    *to_autocomplete = realloc(*to_autocomplete, len + 2);
    (*to_autocomplete)[len] = '*';
    (*to_autocomplete)[len + 1] = '\0';
}
