/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** functions getting options
*/

#include "my.h"
#include "my_maccro.h"

int get_width(string_t *str_s)
{
    int result = 0;

    if (str_s->str[str_s->i] == '0')
        return OTHER;
    while (str_s->str[str_s->i] <= '9'
            && str_s->str[str_s->i] >= '0') {
        result *= 10;
        result += str_s->str[str_s->i] - 48;
        str_s->i++;
    }
    return result;
}

int get_flags(string_t *str_s)
{
    switch (str_s->str[str_s->i]) {
        case '#':
            return HASH;
        case '0':
            return ZERO;
        case '-':
            return MINUS;
        case '+':
            return PLUS;
        case ' ':
            return SPACE;
        break;
    }
    return OTHER;
}

int get_type(string_t *str_s)
{
    switch (str_s->str[str_s->i]) {
        case 'c':
            return C;
        case 'd':
            return D;
        case 'i':
            return I;
        case 'o':
            return OCT;
        case 'u':
            return U;
        case 'p':
            return P;
        break;
    }
    return OTHER;
}

int get_type2(string_t *str_s)
{
    switch (str_s->str[str_s->i]) {
        case 's':
            return S;
        case 'S':
            return SS;
        case 'x':
            return X;
        case 'X':
            return XX;
        case 'b':
            return B;
        case 'f':
            return F;
        case '%':
            return PERCENT;
        break;
    }
    return OTHER;
}

data_stocker_t op_parser(string_t *str_s)
{
    int to_get = 0;
    int data = 0;
    data_stocker_t data_stock = {0, 0, 0, 0, 0, 0, 0, 0};

    while (data_stock.type == 0) {
        data = ARRAY[to_get](str_s);
        if (data && to_get != 1 && to_get != 2)
            str_s->i += 1;
        if (to_get == 1)
            data_stock = put_width(data, data_stock);
        else if (to_get == 2)
            data_stock = put_precision(data, data_stock);
        else
            data_stock = put_in_struct(data, data_stock);
        if (!(data))
            to_get++;
    }
    return data_stock;
}
