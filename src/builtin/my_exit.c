/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** my_exit
*/

#include "my.h"
#include "iterators_prototype.h"
#include "operator_abstract.h"
#include "command.h"
#include "errno.h"
#include "my.h"
#include "shell.h"

define_prototype(command_t);

int my_exit(char **arg, UNUSED char ***env)
{
    if (*arg)
        exit(my_getnbr(*arg));
    else
        exit(0);
}

filedes_t *init_filedes(void)
{
    filedes_t *filedes = malloc(sizeof(filedes_t));

    filedes->input_file_fd = 0;
    return filedes;
}
