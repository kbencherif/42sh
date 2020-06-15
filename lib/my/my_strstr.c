/*
** EPITECH PROJECT, 2019
** function
** File description:
** for library
*/

#include <unistd.h>

int size_finder2(char const *to_find)
{
    int size2 = 0;
    while (to_find[size2] != 0)
        size2 = size2 + 1;
    return (size2);
}

int size_finder1(char *str)
{
    int size = 0;
    while (str[size] != 0)
        size = size + 1;
    return (size);
}

int is_j_equals_to_0(int j, int i)
{
    if (j != 0)
        i = i - 1;
    return (i);
}

char *my_strstr(char *str, char const *to_find)
{
    int size = 0;
    int size2 = 0;
    int j = 0;
    int i = 0;

    size = size_finder1(str);
    size2 = size_finder2(to_find);
    while (size > 0) {
        while  (str[i] == to_find[j]) {
            i = i + 1;
            j = j + 1;
            if (j == size2)
                return (&str[i - j]);
        }
        i = is_j_equals_to_0(j, i);
        j = 0;
        i = i + 1;
        size = size - 1;
    }
    return NULL;
}
