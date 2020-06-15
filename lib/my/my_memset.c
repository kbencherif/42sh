/*
** EPITECH PROJECT, 2019
** my_memset
** File description:
** my_memset
*/

#include <unistd.h>

void *my_memset(void *to_fill, int byte, size_t n)
{
    unsigned char *ptr = to_fill;
    while (n-- > 0)
        *ptr++ = byte;
    return to_fill;
}
