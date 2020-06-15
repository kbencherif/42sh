/*
** EPITECH PROJECT, 2019
** clean line
** File description:
** clean line
*/

#include <stdbool.h>
#include <string.h>

char *erase_space_or_tab(char *cmd, int i)
{
    while (cmd[i]) {
        cmd[i] = cmd[i + 1];
        i++;
    }
    cmd[i] = 0;
    return cmd;
}

void erase_additionnal_spaces(char *line)
{
    bool is_in_cotes = false;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '"' && is_in_cotes == false)
            is_in_cotes = true;
        else if (line[i] == '"' && is_in_cotes == true)
            is_in_cotes = false;
        if (line[i] == ' ' && line[i + 1] == ' ' && !is_in_cotes)
            erase_space_or_tab(line, i--);
    }
}

char *clean_line(char *cmd)
{
    for (int i = 0; cmd[i]; i++)
        if (cmd[i] == '\t')
            cmd[i] = ' ';
    erase_additionnal_spaces(cmd);
    for (int i = 0; cmd[i] == ' '; i++)
        erase_space_or_tab(cmd, i);
    while (cmd && strlen(cmd) && cmd[strlen(cmd) - 1] == ' ')
        cmd[strlen(cmd) - 1] = 0;
    if (cmd[strlen(cmd) - 1] == '\n')
        cmd[strlen(cmd) - 1] = 0;
    return cmd;
}
