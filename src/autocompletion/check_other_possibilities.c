/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** check_other_possibilities
*/

#include "env.h"
#include "my.h"
#include "shell.h"
#include "utils.h"
#include "check_other_possibilities.h"
#include <wordexp.h>
#include <stdbool.h>
#include <string.h>

char **check_other_possibilities(char *to_autocomplete, shell_t *shell)
{
    wordexp_t matches;

    if (is_dir(to_autocomplete)) {
        if (!get_matches(to_autocomplete, &matches))
            return NULL;
    } else
        if (!search_match(to_autocomplete, shell, &matches))
            return NULL;
    matches.we_wordv = clean_matches(matches.we_wordv);
    return matches.we_wordv;
}

bool is_dir(char *line)
{
    for (int i = 0; line[i] ;i++)
        if (line[i] == '/')
            return true;
    return false;
}

bool get_matches(char *to_autocomplet, wordexp_t *p)
{
    if (!wordexp(to_autocomplet, p, 0))
        return true;
    return false;
}

bool search_match(char *to_autocomplet, shell_t *shell, wordexp_t *p)
{
    char **path = my_str_to_word_array(my_getenv("PATH", shell->env), ":");

    if (!wordexp(concate("./", to_autocomplet), p, 0)) {
        for (int i = 0; path[i]; i++) {
            path[i] = concate(path[i], "/");
            path[i] = realloc(path[i], strlen(path[i]) +
                    strlen(to_autocomplet) + 1);
            path[i] = strcat(path[i], to_autocomplet);
            wordexp(path[i], p, WRDE_APPEND);
        }
        return true;
    }
    return false;
}

char **clean_matches(char **matches)
{
    int len = arraylen(matches);
    char **cleaned_match = malloc(sizeof(char *) * (len + 1));
    int j = 0;

    for (int i = 0; i != len; i++) {
        if (!rindex(matches[i], '*')) {
            cleaned_match[j] = rindex(matches[i], '/') + 1;
            j++;
        }
    }
    cleaned_match[j] = NULL;
    return cleaned_match;
}
