/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** get unsigned size
*/

int get_u_nb_size(unsigned int arg)
{
    int i = 1;

    while (arg > 9) {
        arg = arg / 10;
        i++;
    }
    return i;
}
