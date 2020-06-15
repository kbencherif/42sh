/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** put unsigned
*/

#include "my.h"

void my_fput_uns_nbr(FILE *stream, unsigned int nb)
{
    if (nb > 9)
        my_fput_uns_nbr(stream, nb / 10);
    my_fputchar(stream, nb % 10 + 48);
}
