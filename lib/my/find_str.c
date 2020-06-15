/*
** EPITECH PROJECT, 2019
** find str
** File description:
** find str
*/

#include "my.h"
#include <string.h>

int my_strncmp(char *s1, char *s2, int n);

int find_str(char *str, char *to_find)
{
    for (int i = 0; *str; str++, i++) {
        if (my_strncmp(str, to_find, strlen(to_find)))
            return i;
    }
    return -1;
}
