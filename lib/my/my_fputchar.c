/*
** EPITECH PROJECT, 2019
** function
** File description:
** for a library
*/

#include <unistd.h>
#include <stdio.h>

void my_fputchar(FILE *stream, char c)
{
    fwrite(&c, 1, 1, stream);
}
