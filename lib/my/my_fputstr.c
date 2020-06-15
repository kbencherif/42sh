/*
** EPITECH PROJECT, 2019
** function
** File description:
** for a library
*/

#include <unistd.h>
#include <stdio.h>

int my_strlen(const char *str);

int my_fputstr(FILE *stream, char const *str)
{
    int size = my_strlen(str);

    fwrite(str, 1, size, stream);
    return 0;
}
