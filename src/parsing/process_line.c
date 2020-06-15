/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** process line
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "command.h"
#include "shell.h"
#include "my.h"
#include "iterators.h"
#include "env.h"
#include "parsing.h"
#include "execution.h"

void process_line(char *line, shell_t *shell)
{
    char *escape_char = NULL;

    if ((line = clean_line(line))) {
        escape_char = get_escape_char(&line);
        exec_line(line, shell, escape_char);
    }
}
