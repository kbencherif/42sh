/*
** EPITECH PROJECT, 2019
** function
** File description:
** for a library
*/

void my_putchar(char c);

int my_isneg(int nb)
{
    if (nb >= 0) {
        my_putchar(80);
    }
    else {
        my_putchar(78);
    }
    my_putchar('\n');
    return (0);
}
