/*
** EPITECH PROJECT, 2019
** function
** File description:
** for a library
*/

#include <unistd.h>

int my_strlen(const char *str);

int my_putstr(char const *str)
{
    int size = my_strlen(str);

    write(1, str, size);
    return 0;
}
