/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** function printing depending on type
*/

#include "my.h"
#include <stdarg.h>
#include <unistd.h>

int print_str_ss(va_list ap, data_stocker_t data_stocker)
{
    char *str = va_arg(ap, char *);
    int nb_digit = 0;
    int printed = 0;
    int i = 0;

    printed += apply_width(my_strlen(str), data_stocker, 0);
    for ( ; str[i]; i++, nb_digit = 0) {
        if ((str[i] < 32 || str[i] >= 127) && nb_digit == 0) {
            my_putchar('\\');
            nb_digit = get_nb_size(str[i]) + 1;
            printed += 3;
        }
        for ( ; (str[i] < 32 || str[i] >= 127) && nb_digit <= 3; nb_digit++)
            my_putchar('0');
        if (str[i] < 32 || str[i] >= 127)
            my_printf("%o", str[i]);
        else
            my_putchar(str[i]);
    }
    printed += apply_width(my_strlen(str), data_stocker, 1);
    return printed + i;
}

int print_u_int(va_list ap, data_stocker_t data_stocker)
{
    unsigned int arg = va_arg(ap, unsigned int);
    int printed = get_u_nb_size(arg);

    printed += apply_width(get_u_nb_size(arg), data_stocker, 0);
    my_put_uns_nbr(arg);
    printed += apply_width(get_u_nb_size(arg), data_stocker, 1);
    return printed;
}

int print_hexa_x(va_list ap, data_stocker_t data_stocker)
{
    unsigned int arg = va_arg(ap, unsigned int);
    char *tab = my_calloc(get_u_nb_size(arg));
    int i = 0;
    int printed = 0;

    if (data_stocker.hash && data_stocker.zero)
        printed += hash_flag(data_stocker);
    for ( ; arg > 0; i++) {
        if ((arg % 16) > 9)
            tab[i] = ((arg % 16) % 10) + 97;
        else
            tab[i] = arg % 16 + 48;
        arg = arg / 16;
    }
    printed += i;
    printed += apply_width(i, data_stocker, 0);
    if (data_stocker.hash && !(data_stocker.zero))
        printed += hash_flag(data_stocker);
    for (int j = i - 1; j >= 0; j--)
        my_putchar(tab[j]);
    return (printed += apply_width(i, data_stocker, 1));
}

int print_hexa_xx(va_list ap, data_stocker_t data_stocker)
{
    unsigned int arg = va_arg(ap, unsigned int);
    char *tab = my_calloc(get_u_nb_size(arg));
    int i = 0;
    int printed = 0;

    if (data_stocker.hash && data_stocker.zero)
        printed += hash_flag(data_stocker);
    for ( ; arg > 0; i++) {
        if ((arg % 16) > 9)
            tab[i] = ((arg % 16) % 10) + 65;
        else
            tab[i] = arg % 16 + 48;
        arg = arg / 16;
    }
    printed += i;
    printed += apply_width(i, data_stocker, 0);
    if (data_stocker.hash && !(data_stocker.zero))
        printed += hash_flag(data_stocker);
    for (int j = i - 1; j >= 0; j--)
        my_putchar(tab[j]);
    return (printed += apply_width(i, data_stocker, 1));
}

int print_binary(va_list ap, data_stocker_t data_stocker)
{
    unsigned int arg = va_arg(ap, unsigned int);
    unsigned int tab[get_u_nb_size(arg) * 8];
    int i = 0;
    int printed = 0;

    for ( ; arg >= 2; i++) {
        tab[i] = arg % 2;
        arg = arg / 2;
    }
    tab[i] = arg;
    printed += i + 1;
    printed += apply_width(i + 1, data_stocker, 0);
    for (int j = i; j >= 0; j--)
        my_put_nbr(tab[j]);
    printed += apply_width(i + 1, data_stocker, 1);
    return printed;
}
