/*
** EPITECH PROJECT, 2019
** function
** File description:
** for a library
*/

int my_compute_power_rec(int nb, int power)
{

    if (power == 0)
        return (1);
    if (power < 0 || nb > 2147483647) {
        return (0);
    }
    if (power == 1)
        return (nb);
    return nb * my_compute_power_rec(nb, power - 1);
}
