/*
** EPITECH PROJECT, 2019
** my_str_to_word_array
** File description:
** task04
*/

#include <string.h>
#include <stddef.h>
#include <stdlib.h>

int my_strlen(char const *str);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strdup(char const *src);
char *clean_line(char *cmd);

int nbr_of_tab(char const *str, char *delim)
{
    int tab = 0;
    int i = 0;

    if (!str)
        return 0;
    while (*str) {
        if (strncmp(str, delim, strlen(delim)) >= 0)
            tab = tab + 1;
        i = i + 1;
        str++;
    }
    return (tab + 1);
}

char **my_str_to_word_array(char *str, char *delim)
{
    char **returned = malloc(sizeof(char *)
        * (nbr_of_tab(str, delim) + 1));
    char *buffer = NULL;
    int i = 1;

    if (!str)
        return NULL;
    returned[0] = strdup(strtok(strdup(str), delim));
    for (; (buffer = strtok(NULL, delim)); i++)
        returned[i] = strdup(clean_line(buffer));
    returned[i] = NULL;
    return returned;
}
