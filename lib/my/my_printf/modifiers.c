/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** functions changing string according to a flag
*/

#include "my.h"
#include "my_maccro.h"

int hash_flag(data_stocker_t data_stocker)
{
    switch (data_stocker.type) {
        case OCT:
            my_putchar('0');
            return 1;
        case X:
            my_putstr("0x");
            return 2;
        case XX:
            my_putstr("0X");
            return 2;
        break;
    }
    return 0;
}

int get_shift(data_stocker_t data_stocker, int size)
{
    int shift = (data_stocker.width - size);

    if (data_stocker.hash && data_stocker.type == OCT)
        shift -= 1;
    else if (data_stocker.hash && (data_stocker.type == X
                || data_stocker.type == XX || data_stocker.type == OCT))
        shift -= 2;
    if ((data_stocker.plus || data_stocker.space) && (data_stocker.type == D
                || data_stocker.type == I))
        shift -= 1;
    if (data_stocker.type != C && data_stocker.type != SS
            && data_stocker.type != S
            && data_stocker.type != B && data_stocker.precision - size > 0)
        shift -= data_stocker.precision - size;
    return shift;
}

int apply_precision(data_stocker_t data_stocker, int size)
{
    int precision = data_stocker.precision - size;
    int printed = 0;

    for ( ; precision > 0 && data_stocker.type != C && data_stocker.type != SS
            && data_stocker.type != S && data_stocker.type != F
            && data_stocker.type != B; precision--) {
        printed += 1;
        my_putchar('0');
    }
    return printed;
}

int apply_width(int size, data_stocker_t data_stocker, int pos)
{
    int shift = get_shift(data_stocker, size);
    int printed = 0;

    for ( ; shift > 0 && !(data_stocker.minus) && !pos; shift--) {
        if (data_stocker.zero && !(data_stocker.minus)
                && data_stocker.type != C)
            my_putchar('0');
        else
            my_putchar(' ');
        printed += 1;
    }
    if (!pos)
        printed += apply_precision(data_stocker, size);
    for ( ; shift > 0 && data_stocker.minus && pos; printed += 1, shift--) {
        if (data_stocker.zero && !(data_stocker.minus)
                && data_stocker.type != C)
            my_putchar('0');
        else
            my_putchar(' ');
    }
    return printed;
}

int plus_space_flag(data_stocker_t data_stocker)
{
    if (data_stocker.plus)
        my_putchar('+');
    if (data_stocker.space && !(data_stocker.plus))
        my_putchar(' ');
    return 1;
}
