/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** quote cleaner
*/

void shift_charptr(char *str, int i)
{
    for (; str[i]; i++)
        str[i] = str[i + 1];
}

void clean_quote(char *str)
{
    int i = 0;

    for (; str[i]; i++)
        if (str[i] == '\'' || str[i] == '"')
            shift_charptr(str, i);
}
