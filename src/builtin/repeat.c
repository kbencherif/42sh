/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** alias built_in
*/

#include <unistd.h>
#include <string.h>
#include "shell.h"
#include "operator_abstract.h"
#include "my.h"

int arraylen(char **array);
void process_line(char *line, shell_t *shell);

bool is_nb(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] < '0' or str[i] > '9')
            return false;
    return true;
}

char *convert_db_arr_to_str(char **arg)
{
    char *str = NULL;

    for (int i = 1; arg[i]; i++) {
        if (not str)
            str = strdup(arg[i]);
        else
            str = concate(str, concate(" ", arg[i]));
    }
    return str;
}

int my_repeat(char **arg, void *shell_s)
{
    int count = 0;
    shell_t *shell = (shell_t *) shell_s;
    char *repeated_cmd = NULL;

    if (not arg or arraylen(arg) < 2) {
        write(2, "repeat: Too few arguments.\n", 27);
        return 1;
    }
    if (is_nb(arg[0]))
        count = my_getnbr(arg[0]);
    else {
        write(2, "repeat: Badly formed number.\n", 29);
        return 1;
    }
    repeated_cmd = convert_db_arr_to_str(arg);
    while (count--)
        process_line(repeated_cmd, shell);
    return my_getnbr(get_variable(shell, "?"));
}
