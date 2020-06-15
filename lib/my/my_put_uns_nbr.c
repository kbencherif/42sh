/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** put unsigned
*/

#include "my.h"

void my_put_uns_nbr(unsigned int nb)
{
    if (nb > 9)
        my_put_uns_nbr(nb / 10);
    my_putchar(nb % 10 + 48);
}
