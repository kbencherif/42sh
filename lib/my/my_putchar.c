/*
** EPITECH PROJECT, 2019
** function
** File description:
** for a library
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
