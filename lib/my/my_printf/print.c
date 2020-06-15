/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** functions printing
*/

#include "my.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int print_start(string_t *str_s, int j)
{
    int printed = 0;

    for ( ; str_s->str[j] != '%' && str_s->str[j] != 0; j++) {
        my_putchar(str_s->str[j]);
        printed++;
    }
    str_s->i++;
    return printed;
}

int print_int(va_list ap, data_stocker_t data_stocker)
{
    int arg = va_arg(ap, int);
    int printed = get_nb_size(arg);
    int i = 0;

    if (arg < 0) {
        if (!data_stocker.plus)
            i++;
        printed++;
        if (data_stocker.zero)
            my_printf("%c", '-');
    }
    else if (data_stocker.plus || data_stocker.space)
        printed += plus_space_flag(data_stocker);
    printed += apply_width(get_nb_size(arg) + i, data_stocker, 0);
    if (arg < 0 && !data_stocker.zero)
        my_printf("%c", '-');
    my_put_u_nbr(arg);
    printed += apply_width(get_nb_size(arg) + i, data_stocker, 1);
    return printed;
}

int print_octal(va_list ap, data_stocker_t data_stocker)
{
    unsigned int arg = va_arg(ap, unsigned int);
    unsigned int tab[get_u_nb_size(arg)];
    int i = 0;
    int printed = 0;

    if (data_stocker.hash)
        printed += hash_flag(data_stocker);
    for ( ; arg >= 8; i++) {
        tab[i] = arg % 8;
        arg = arg / 8;
    }
    tab[i] = arg;
    printed += i + 1;
    printed += apply_width(i + 1, data_stocker, 0);
    for (int j = i ; j >= 0; j--)
        my_put_nbr(tab[j]);
    printed += apply_width(i + 1, data_stocker, 1);
    return printed;
}

int print_char(va_list ap, data_stocker_t data_stocker)
{
    int arg = va_arg(ap, int);
    int printed = 0;

    printed += apply_width(1, data_stocker, 0);
    my_putchar(arg);
    printed += apply_width(1, data_stocker, 1);
    return printed + 1;
}

int print_str(va_list ap, data_stocker_t data_stocker)
{
    char *str = my_strdup(va_arg(ap, char *));
    int printed = 0;

    if (data_stocker.precision)
        str[data_stocker.precision] = 0;
    printed = my_strlen(str);
    printed += apply_width(my_strlen(str), data_stocker, 0);
    my_putstr(str);
    printed += apply_width(my_strlen(str), data_stocker, 1);
    free(str);
    return printed;
}
