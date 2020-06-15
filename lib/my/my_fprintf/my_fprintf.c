/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** my_printf.c
*/

#include <stdio.h>
#include <stdarg.h>
#include "my.h"
#include "my_struct.h"
#include "my_maccro.h"

static const t_fmodifiers_t MOD[] = {
    {D, fprint_int},
    {I, fprint_int},
    {C, fprint_char},
    {OCT, fprint_octal},
    {S, fprint_str},
    {SS, fprint_str_ss},
    {U, fprint_u_int},
    {X, fprint_hexa_x},
    {XX, fprint_hexa_xx},
    {B, fprint_binary},
    {P, fprint_address},
    {F, fprint_float},
    {PERCENT, fprint_percent},
    {0, NULL}
};

int fprint_percent(UNUSED va_list ap, UNUSED data_stocker_t data_stocker,
                FILE *stream)
{
    int printed = 0;

    my_fputchar(stream, '%');
    return printed + 1;
}

int fformat_arg(va_list ap, data_stocker_t data_stocker, FILE *stream)
{
    int printed = 0;

    for (int i = 0; MOD[i].fprint_func; i++) {
        if (data_stocker.type == MOD[i].type)
            printed = MOD[i].fprint_func(ap, data_stocker, stream);
    }
    return printed;
}

int fcheck_valid(string_t *str_s, int *j, FILE *stream)
{
    int valid = 0;
    int printed = 0;
    int buf = str_s->i;

    str_s->i++;
    for ( ; str_s->str[str_s->i] != '%' && str_s->str[str_s->i]
            && (!get_type(str_s) && !get_type2(str_s)); str_s->i++) {
        valid += get_flags(str_s);
        valid += get_width(str_s);
        valid += get_precision(str_s);
        valid += get_type(str_s);
        valid += get_type2(str_s);
        if (!valid) {
            my_fputchar(stream, '%');
            *j = str_s->i;
            printed += fprint_start(str_s, *j, stream);
            return (*j = printed + 1);
        }
    }
    str_s->i = buf;
    return printed;
}

int my_fprintf(FILE *stream, const char *str, ...)
{
    va_list ap;
    int j = 0;
    int printed = 0;
    string_t str_s = {str, 0};

    va_start(ap, str);
    for (data_stocker_t data_stock; str_s.i < my_strlen(str_s.str) - 1; ) {
        if (str_s.str[str_s.i] == '%')
            printed += fcheck_valid(&str_s, &j, stream);
        if (str_s.str[str_s.i] == '%') {
            printed += fprint_start(&str_s, j, stream);
            data_stock = op_parser(&str_s);
            printed += fformat_arg(ap, data_stock, stream);
            j = str_s.i;
        } else
            str_s.i++;
    }
    return (printed += fprint_start(&str_s, j, stream));
}
