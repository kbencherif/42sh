/*
** EPITECH PROJECT, 2019
** my_itoa
** File description:
** lib func
*/

#include "my.h"

char *my_itoa(int number)
{
    char *nb = my_calloc(get_nb_size(number) + 1);
    int buf;
    int i = 0;

    if (number == 0)
        nb[0] = number + 48;
    while (number > 0) {
        buf = number % 10;
        number /= 10;
        nb[i++] = buf + 48;
    }
    my_revstr(nb);
    return nb;
}
