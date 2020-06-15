/*
** EPITECH PROJECT, 2019
** function
** File description:
** for a library
*/

int my_getnbr(char const *str)
{
    int nega = 1;
    long result = 0;
    int i = 0;
    int particular = 2147483647;
    int particular2 = -2147483648;

    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            nega = nega * -1;
        i++;
    }
    while (str[i] <= '9' && str[i] >= '0') {
        result *= 10;
        result += str[i] - 48;
        i++;
    }
    if (result > particular || result < particular2)
        return (0);
    return (result * nega);
}
