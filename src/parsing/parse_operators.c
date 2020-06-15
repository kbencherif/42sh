/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** parse cmd operators
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "built_in.h"
#include "command.h"
#include "operator_abstract.h"
#include "parsing.h"

void erase_operator_and_arg_from_argv(char ***argv, char *operator_arg)
{
    bool arg_erased = false;
    bool operator_erased = false;

    if (!operator_arg)
        return;
    for (int i = 0; (*argv)[i]; i++) {
        if (is_redirect((*argv)[i]) and !operator_erased) {
            *argv = delete_from_array((*argv), i);
            operator_erased = true;
            i = -1;
        } else if (my_strcmp((*argv)[i], operator_arg)
            and !arg_erased) {
            *argv = delete_from_array((*argv), i);
            arg_erased = true;
            i = -1;
        }
    }
}

void format_argv_for_execution(command_t *command, char ***argv)
{
    int i = 0;

    erase_operator_and_arg_from_argv(argv, command->input_op_arg);
    erase_operator_and_arg_from_argv(argv, command->output_op_arg);
    command->argv = array_cpy(*argv);
    for (; (*argv)[i]; i++) {
        if (is_pipe((*argv)[i])) {
            command->argv[i] = NULL;
            (*argv) += i + 1;
            return;
        }
    }
    (*argv) += i;
}

void get_operator_and_arg(command_t *command, char **argv)
{
    int redirection = _;

    for (int i = 0; argv[i] and not is_pipe(argv[i]); i++) {
        redirection = get_redirection(argv, i);
        if (redirection is RED_OUT or redirection is RED_OUT_A) {
            command->red_output_op = redirection;
            command->output_op_arg = argv[i + 1];
        } else if (redirection is RED_STDIN or redirection is RED_IN) {
            command->red_input_op = redirection;
            command->input_op_arg = argv[i + 1];
        }
    }
}
