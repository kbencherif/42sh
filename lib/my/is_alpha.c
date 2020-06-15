/*
** EPITECH PROJECT, 2019
** is_alphanumeric
** File description:
** lib func
*/

int is_alpha(char c)
{
    if (c >= 'A' && c <= 'Z')
        c += 32;
    if (c >= 'a' && c <= 'z')
        return 1;
    return 0;
}

