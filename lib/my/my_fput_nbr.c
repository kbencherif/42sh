/*
** EPITECH PROJECT, 2019
** function
** File description:
** for a library
*/

#include <unistd.h>
#include <stdio.h>

void my_fputchar(FILE* stream, char c);

void my_fput_nbr(FILE* stream, int nb)
{
    if (nb < 0) {
        my_fputchar(stream, '-');
        nb = -nb;
    }
    if (nb > 9)
        my_fput_nbr(stream, nb / 10);
    my_fputchar(stream, nb % 10 + 48);
}
