/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** check_builtin
*/

#include "built_in.h"
#include <string.h>
#include "my.h"

char **check_builtin_match(char *to_autocomplete)
{
    char *match = NULL;
    int len = strlen(to_autocomplete);
    int match_len = 0;

    for (int i = 0; FUNC[i].name; i++) {
        if (!strncmp(to_autocomplete, FUNC[i].name, len)) {
            match = match ? concate(match, FUNC[i].name) :
                strndup(FUNC[i].name, find_char(FUNC[i].name, '='));
            match_len = strlen(match);
            match = realloc(match, match_len + 2);
            match[match_len] = ':';
            match[match_len + 1] = '\0';
        }
    }
    return my_str_to_word_array(match, ":");
}
