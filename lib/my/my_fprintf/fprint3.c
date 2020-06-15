/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** my_printf prnt func
*/

#include "my.h"
#include <stdarg.h>

int fprint_address(va_list ap, data_stocker_t data_stocker, FILE *stream)
{
    long addr = va_arg(ap, long);
    char *tab = my_calloc(get_nb_size(addr + 10));
    int printed = 2;
    int i = 0;

    my_fputstr(stream, "0x");
    for ( ; addr > 0; i++) {
        if ((addr % 16) > 9)
            tab[i] = ((addr % 16) % 10) + 97;
        else
            tab[i] = addr % 16 + 48;
        addr = addr / 16;
    }
    printed += i;
    printed += fapply_width(i, data_stocker, 0, stream);
    for (int j = i - 1; j >= 0; j--)
        my_fputchar(stream, tab[j]);
    printed += fapply_width(i, data_stocker, 1, stream);
    return printed;
}

int fprint_float(va_list ap, data_stocker_t data_stocker, FILE *stream)
{
    double nb = va_arg(ap, double);
    int buf = nb;
    int printed = 0;
    char *tab = my_calloc(get_nb_size(buf) + data_stocker.precision);
    int size = get_nb_size(buf);
    int i = 0;

    printed += fapply_width(i, data_stocker, 0, stream);
    for (; data_stocker.precision; data_stocker.precision--, buf = nb)
        nb *= 10;
    for (; buf > 0; i++) {
        tab[i] = (buf % 10) + 48;
        buf = buf / 10;
    }
    printed += i;
    for (int j = i - 1; j >= 0; j--) {
        my_fputchar(stream, tab[j]);
        if (j == i - size)
            my_fputchar(stream, '.');
    }
    return (printed += fapply_width(i, data_stocker, 1, stream));
}
