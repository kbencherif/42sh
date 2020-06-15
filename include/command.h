/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** command include
*/

#ifndef COMMAND_H_
#define COMMAND_H_
#include "shell.h"
#include <stdbool.h>

enum {
    NONE = 0,
    OR = 1,
    AND = 2,
    PARENTHESIS,
    BACKTICKS,
};

typedef struct cmd_list {
    char *cmd;
    int execution;
} cmd_list_t;

typedef struct unparsed_cmd {
    char *cmd;
    int condition_exec;
    int special_exec;
} unparsed_cmd_t;

typedef struct command {
    char *executable_name;
    char *path;
    char **argv;
    int red_input_op;
    char *input_op_arg;
    int red_output_op;
    char *output_op_arg;
} command_t;

typedef struct filedes {
    int *pipes_fd;
    int *usr_input_pipe;
    int input_file_fd;
} filedes_t;

enum {
    _,
    RED_OUT,
    RED_OUT_A,
    RED_IN,
    RED_STDIN,
};

#endif /* ifndef COMMAND_H_ */
