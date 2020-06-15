/*
** EPITECH PROJECT, 2020
** find_char.c
** File description:
** find a char in a given string
*/

int find_char(char *str, char c)
{
    int i = 0;

    while (str[i] != c && str[i] != '\0')
        i++;
    if (str[i] == c)
        return i;
    else
        return -1;
}
