/*
** EPITECH PROJECT, 2020
** parce_escape_char
** File description:
** .c
*/

#include <stddef.h>
#include <stdlib.h>

int change_backslash(char *argument, char *escape_char, int i)
{
    for (int j = 0; argument[j] != '\0'; j++) {
        if (argument[j] == '\\') {
            argument[j] = escape_char[i];
            i++;
        }
    }
    return (i);
}

void change_escape_char(char ***arguments, char *escape_char)
{
    int escape_nb = 0;

    for (int i = 0; (*arguments)[i] != NULL; i++)
        escape_nb = change_backslash((*arguments)[i], escape_char, escape_nb);
}

void erase_escape_char(char *cmdptr, int i)
{
    for (int j = i; cmdptr[j] != '\0'; j++) {
        cmdptr[j] = cmdptr[j + 1];
        if (cmdptr[j + 1] == '\0')
            cmdptr[j] = '\0';
    }
}

char *get_escape_char(char **cmdptr)
{
    int backslash_nb = 0;
    int j = 0;
    char *escape_char = NULL;

    for (int i = 0; (*cmdptr)[i] != '\0'; i++)
        if ((*cmdptr)[i] == '\\' && (*cmdptr)[i + 1] != '\0')
            backslash_nb += 1;
    escape_char = malloc(sizeof(char) * (backslash_nb + 1));
    for (int i = 0; (*cmdptr)[i] != '\0'; i++) {
        if ((*cmdptr)[i] == '\\' && (*cmdptr)[i + 1] != '\0') {
            escape_char[j] = (*cmdptr)[i + 1];
            j++;
            erase_escape_char((*cmdptr), (i + 1));
        }
    }
    escape_char[backslash_nb] = '\0';
    return (escape_char);
}
