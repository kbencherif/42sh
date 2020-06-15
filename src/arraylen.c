/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** arraylen
*/

int arraylen(char **array)
{
    int len = 0;

    if (!array || !array[0])
        return len;
    for ( ; array[len]; len++);
    return len;
}
