/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** autocompletion
*/

#ifndef __AUTOCOMPLET__
#define __AUTOCOMPLET__

#include "read_line.h"
#include "shell.h"

bool matched_multiples_times(char **to_check);
void add_star(char **to_autocomplete);
char **check_builtin_match(char *to_autocomplete);
void display_match(char **match, char *prompt, edit_line_t *line,
        char *to_find);
char **check_other_possibilities(char *to_autocomplete, shell_t *shell);
char *copy_to_autocomplete_word(edit_line_t *line);
void autocompletion(char *prompt, edit_line_t *line, shell_t *shell);
char **check_var(char *to_autocomplete, shell_t *shell);

#endif
