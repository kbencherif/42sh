/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** script exec
*/

#include "command.h"
#include "shell.h"
#include "my.h"
#include "iterators.h"
#include "operator_abstract.h"
#include "read_line.h"
#include "env.h"
#include "parsing.h"
#include "execution.h"
#include <stdio.h>
#include <unistd.h>

int exec_script(const char *file, shell_t *shell)
{
    FILE *script_file = fopen(file, "r");
    size_t n = 0;
    char *line = NULL;

    if (not file) {
        printf("%s: No such file or directory.\n", file);
        exit(84);
    }
    while (getline(&line, &n, script_file) != -1) {
        process_line(line, shell);
    }
    exit(my_getnbr(get_variable(shell, "?")));
}
