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

static const t_modifiers_t MOD[] = {
    {D, print_int},
    {I, print_int},
    {C, print_char},
    {OCT, print_octal},
    {S, print_str},
    {SS, print_str_ss},
    {U, print_u_int},
    {X, print_hexa_x},
    {XX, print_hexa_xx},
    {B, print_binary},
    {P, print_address},
    {F, print_float},
    {PERCENT, print_percent},
    {0, NULL}
};

int print_percent(UNUSED va_list ap, UNUSED data_stocker_t data_stocker)
{
    int printed = 0;

    my_putchar('%');
    return printed + 1;
}

int format_arg(va_list ap, data_stocker_t data_stocker)
{
    int printed = 0;

    for (int i = 0; MOD[i].print_func; i++) {
        if (data_stocker.type == MOD[i].type)
            printed = MOD[i].print_func(ap, data_stocker);
    }
    return printed;
}

int check_valid(string_t *str_s, int *j)
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
            my_putchar('%');
            *j = str_s->i;
            printed += print_start(str_s, *j);
            return (*j = printed + 1);
        }
    }
    str_s->i = buf;
    return printed;
}

int my_printf(const char *str, ...)
{
    va_list ap;
    int j = 0;
    int printed = 0;
    string_t str_s = {str, 0};

    va_start(ap, str);
    for (data_stocker_t data_stock; str_s.i < my_strlen(str_s.str) - 1; ) {
        if (str_s.str[str_s.i] == '%')
            printed += check_valid(&str_s, &j);
        if (str_s.str[str_s.i] == '%') {
            printed += print_start(&str_s, j);
            data_stock = op_parser(&str_s);
            printed += format_arg(ap, data_stock);
            j = str_s.i;
        } else
            str_s.i++;
    }
    return (printed += print_start(&str_s, j));
}
