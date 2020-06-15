/*
** EPITECH PROJECT, 2019
** function
** File description:
** for library
*/

char *my_revstr(char *str)
{
    int i = 0;
    int len = 0;
    int buffer = 0;

    for (; str[len]; len++);
    len -= 1;
    while (len > i) {
        buffer = str[len];
        str[len] = str[i];
        str[i] = buffer;
        i++;
        len--;
    }
    return (str);
}
