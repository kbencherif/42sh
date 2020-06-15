/*
** EPITECH PROJECT, 2019
** lib
** File description:
** delete from array
*/

char **delete_from_array(char **array, int i)
{
    for (; array[i]; i++)
        array[i] = array[i + 1];
    return array;
}
