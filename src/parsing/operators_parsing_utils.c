/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** operators parsing utils
*/

#include "my.h"
#include "command.h"
#include "operator_abstract.h"

int is_double_op(char **operator_tab, char **cmd, int i)
{
    for (int j = 0; operator_tab[j]; j++) {
        if (my_strcmp(cmd[i], operator_tab[j]) and cmd[i + 1]
            and my_strcmp(cmd[i + 1], operator_tab[j])) {
            return j;
        }
    }
    return -1;
}

char **concate_double_operators(char **cmd)
{
    char *operator_tab[] = {"<", ">", "&", "|", NULL};
    int index = -1;

    for (int i = 0; cmd[i]; i++) {
        if ((index = is_double_op(operator_tab, cmd, i)) != -1) {
            cmd = delete_from_array(cmd, i);
            cmd[i] = concate(cmd[i], operator_tab[index]);
            i = -1;
        }
    }
    return cmd;
}

bool is_redirect(char *c)
{
    return my_strcmp(c, "<") || my_strcmp(c, ">")
        || my_strcmp(c, "<<") || my_strcmp(c, ">>");
}

bool is_pipe(char *c)
{
    return my_strcmp(c, "|");
}

int get_redirection(char **argv, int i)
{
    if (my_strcmp(argv[i], "<<"))
        return RED_STDIN;
    if (my_strcmp(argv[i], "<"))
        return RED_IN;
    if (my_strcmp(argv[i], ">>"))
        return RED_OUT_A;
    if (my_strcmp(argv[i], ">"))
        return RED_OUT;
    return _;
}
