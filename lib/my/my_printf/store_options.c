/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** functions acting on stocking options in strucure
*/

#include "my_maccro.h"
#include "my.h"

data_stocker_t put_in_struct(int data, data_stocker_t data_stock)
{
    switch (data) {
        case HASH:
            data_stock.hash = 1;
            break;
        case MINUS:
            data_stock.minus = 1;
            break;
        case PLUS:
            data_stock.plus = 1;
            break;
        case SPACE:
            data_stock.space = 1;
            break;
        case ZERO:
            data_stock.zero = 1;
            break;
    }
    if (data >= C && data <= PERCENT && data_stock.type == 0)
        data_stock.type = data;
    return data_stock;
}

int get_precision(string_t *str_s)
{
    int buff = 0;

    if (str_s->str[str_s->i] == '.' && str_s->str[str_s->i + 1] <= '9'
            && str_s->str[str_s->i + 1] >= '0') {
        str_s->i++;
        buff = my_getnbr(str_s->str + str_s->i);
        str_s->i += get_nb_size(buff);
    }
    else if (str_s->str[str_s->i] == '.')
        str_s->i++;
    return buff;
}

data_stocker_t put_precision(int data, data_stocker_t data_stocker)
{
    if (data)
        data_stocker.precision = data;
    return data_stocker;
}

data_stocker_t put_width(int data, data_stocker_t data_stock)
{
    if (data)
        data_stock.width = data;
    return data_stock;
}

int get_nb_size(int arg)
{
    int i = 1;

    while (arg > 9) {
        arg = arg / 10;
        i++;
    }
    return i;
}
