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

int fprint_start(string_t *str_s, int j, FILE* stream)
{
    int printed = 0;

    for ( ; str_s->str[j] != '%' && str_s->str[j] != 0; j++) {
        my_fputchar(stream, str_s->str[j]);
        printed++;
    }
    str_s->i++;
    return printed;
}

int fprint_int(va_list ap, data_stocker_t data_stocker, FILE* stream)
{
    int arg = va_arg(ap, int);
    int printed = get_nb_size(arg);
    int i = 0;

    if (arg < 0) {
        if (!data_stocker.plus)
            i++;
        printed++;
        if (data_stocker.zero)
            my_fprintf(stream, "%c", '-');
    }
    else if (data_stocker.plus || data_stocker.space)
        printed += plus_space_flag(data_stocker);
    printed += fapply_width(get_nb_size(arg) + i, data_stocker, 0, stream);
    if (arg < 0 && !data_stocker.zero)
        my_fprintf(stream, "%c", '-');
    my_fput_u_nbr(stream, arg);
    printed += fapply_width(get_nb_size(arg) + i, data_stocker, 1, stream);
    return printed;
}

int fprint_octal(va_list ap, data_stocker_t data_stocker, FILE *stream)
{
    unsigned int arg = va_arg(ap, unsigned int);
    unsigned int tab[get_u_nb_size(arg)];
    int i = 0;
    int printed = 0;

    if (data_stocker.hash)
        printed += fhash_flag(data_stocker, stream);
    for ( ; arg >= 8; i++) {
        tab[i] = arg % 8;
        arg = arg / 8;
    }
    tab[i] = arg;
    printed += i + 1;
    printed += fapply_width(i + 1, data_stocker, 0, stream);
    for (int j = i ; j >= 0; j--)
        my_fput_nbr(stream, tab[j]);
    printed += fapply_width(i + 1, data_stocker, 1, stream);
    return printed;
}

int fprint_char(va_list ap, data_stocker_t data_stocker, FILE *stream)
{
    int arg = va_arg(ap, int);
    int printed = 0;

    printed += fapply_width(1, data_stocker, 0, stream);
    my_fputchar(stream, arg);
    printed += fapply_width(1, data_stocker, 1, stream);
    return printed + 1;
}

int fprint_str(va_list ap, data_stocker_t data_stocker, FILE *stream)
{
    char *str = my_strdup(va_arg(ap, char *));
    int printed = 0;

    if (data_stocker.precision)
        str[data_stocker.precision] = 0;
    printed = my_strlen(str);
    printed += fapply_width(my_strlen(str), data_stocker, 0, stream);
    my_fputstr(stream, str);
    printed += fapply_width(my_strlen(str), data_stocker, 1, stream);
    free(str);
    return printed;
}
