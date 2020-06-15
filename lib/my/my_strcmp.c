/*
** EPITECH PROJECT, 2019
** lib func
** File description:
** my_strcmp
*/

#include "my.h"

int my_strcmp(char *s1, char *s2)
{
    if (!s1 || !s2 || my_strlen(s1) != my_strlen(s2))
        return 0;
    for (int i = 0; s1[i]; i++) {
        if (s1[i] != s2[i])
            return 0;
    }
    return 1;
}
