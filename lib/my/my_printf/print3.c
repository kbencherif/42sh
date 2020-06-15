/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** my_printf prnt func
*/

#include "my.h"
#include <stdarg.h>

int print_address(va_list ap, data_stocker_t data_stocker)
{
    long addr = va_arg(ap, long);
    char *tab = my_calloc(get_nb_size(addr + 10));
    int printed = 2;
    int i = 0;

    my_putstr("0x");
    for ( ; addr > 0; i++) {
        if ((addr % 16) > 9)
            tab[i] = ((addr % 16) % 10) + 97;
        else
            tab[i] = addr % 16 + 48;
        addr = addr / 16;
    }
    printed += i;
    printed += apply_width(i, data_stocker, 0);
    for (int j = i - 1; j >= 0; j--)
        my_putchar(tab[j]);
    printed += apply_width(i, data_stocker, 1);
    return printed;
}

int print_float(va_list ap, data_stocker_t data_stocker)
{
    double nb = va_arg(ap, double);
    int buf = nb;
    int printed = 0;
    char *tab = my_calloc(get_nb_size(buf) + data_stocker.precision);
    int size = get_nb_size(buf);
    int i = 0;

    printed += apply_width(i, data_stocker, 0);
    for (; data_stocker.precision; data_stocker.precision--, buf = nb)
        nb *= 10;
    for ( ; buf > 0; i++) {
        tab[i] = (buf % 10) + 48;
        buf = buf / 10;
    }
    printed += i;
    for (int j = i - 1; j >= 0; j--) {
        my_putchar(tab[j]);
        if (j == i - size)
            my_putchar('.');
    }
    return (printed += apply_width(i, data_stocker, 1));
}
