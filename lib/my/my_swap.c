/*
** EPITECH PROJECT, 2019
** function
** File description:
** for a library
*/

void my_swap(void *a, void *b)
{
    void *z = a;

    a = b;
    b = z;
}
