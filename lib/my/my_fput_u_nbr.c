/*
** EPITECH PROJECT, 2019
** lib
** File description:
** my_put_u_nbr
*/

#include <unistd.h>
#include <stdio.h>

void my_fputchar(FILE *stream, char c);

void my_fput_u_nbr(FILE* stream, int nb)
{
    if (nb < 0) {
        nb = -nb;
    }
    if (nb > 9)
        my_fput_u_nbr(stream, nb / 10);
    my_fputchar(stream, nb % 10 + 48);
}
