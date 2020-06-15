/*
** EPITECH PROJECT, 2019
** function
** File description:
** for a library
*/

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != 0) {
        i++;
    }
    return (i);
}
