/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** function printing depending on type
*/

#include "my.h"
#include <stdarg.h>
#include <unistd.h>

int fprint_str_ss(va_list ap, data_stocker_t data_stocker, FILE *stream)
{
    char *str = va_arg(ap, char *);
    int nb_digit = 0;
    int printed = 0;
    int i = 0;

    printed += fapply_width(my_strlen(str), data_stocker, 0, stream);
    for ( ; str[i]; i++, nb_digit = 0) {
        if ((str[i] < 32 || str[i] >= 127) && nb_digit == 0) {
            my_fputchar(stream, '\\');
            nb_digit = get_nb_size(str[i]) + 1;
            printed += 3;
        }
        for ( ; (str[i] < 32 || str[i] >= 127) && nb_digit <= 3; nb_digit++)
            my_fputchar(stream, '0');
        if (str[i] < 32 || str[i] >= 127)
            my_fprintf(stream, "%o", str[i]);
        else
            my_fputchar(stream, str[i]);
    }
    printed += fapply_width(my_strlen(str), data_stocker, 1, stream);
    return printed + i;
}

int fprint_u_int(va_list ap, data_stocker_t data_stocker, FILE *stream)
{
    unsigned int arg = va_arg(ap, unsigned int);
    int printed = get_u_nb_size(arg);

    printed += fapply_width(get_u_nb_size(arg), data_stocker, 0, stream);
    my_fput_uns_nbr(stream, arg);
    printed += fapply_width(get_u_nb_size(arg), data_stocker, 1, stream);
    return printed;
}

int fprint_hexa_x(va_list ap, data_stocker_t data_stocker, FILE *stream)
{
    unsigned int arg = va_arg(ap, unsigned int);
    char *tab = my_calloc(get_u_nb_size(arg));
    int i = 0;
    int printed = 0;

    if (data_stocker.hash && data_stocker.zero)
        printed += fhash_flag(data_stocker, stream);
    for ( ; arg > 0; i++) {
        if ((arg % 16) > 9)
            tab[i] = ((arg % 16) % 10) + 97;
        else
            tab[i] = arg % 16 + 48;
        arg = arg / 16;
    }
    printed += i;
    printed += fapply_width(i, data_stocker, 0, stream);
    if (data_stocker.hash && !(data_stocker.zero))
        printed += fhash_flag(data_stocker, stream);
    for (int j = i - 1; j >= 0; j--)
        my_fputchar(stream, tab[j]);
    return (printed += fapply_width(i, data_stocker, 1, stream));
}

int fprint_hexa_xx(va_list ap, data_stocker_t data_stocker, FILE *stream)
{
    unsigned int arg = va_arg(ap, unsigned int);
    char *tab = my_calloc(get_u_nb_size(arg));
    int i = 0;
    int printed = 0;

    if (data_stocker.hash && data_stocker.zero)
        printed += fhash_flag(data_stocker, stream);
    for ( ; arg > 0; i++) {
        if ((arg % 16) > 9)
            tab[i] = ((arg % 16) % 10) + 65;
        else
            tab[i] = arg % 16 + 48;
        arg = arg / 16;
    }
    printed += i;
    printed += fapply_width(i, data_stocker, 0, stream);
    if (data_stocker.hash && !(data_stocker.zero))
        printed += fhash_flag(data_stocker, stream);
    for (int j = i - 1; j >= 0; j--)
        my_fputchar(stream, tab[j]);
    return (printed += fapply_width(i, data_stocker, 1, stream));
}

int fprint_binary(va_list ap, data_stocker_t data_stocker, FILE *stream)
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
    printed += fapply_width(i + 1, data_stocker, 0, stream);
    for (int j = i; j >= 0; j--)
        my_fput_nbr(stream, tab[j]);
    printed += fapply_width(i + 1, data_stocker, 1, stream);
    return printed;
}
