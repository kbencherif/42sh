/*
** EPITECH PROJECT, 2019
** lib
** File description:
** my_put_u_nbr
*/

#include <unistd.h>

void my_putchar(char c);

void my_put_u_nbr(int nb)
{
    if (nb < 0) {
        nb = -nb;
    }
    if (nb > 9)
        my_put_u_nbr(nb / 10);
    my_putchar(nb % 10 + 48);
}
