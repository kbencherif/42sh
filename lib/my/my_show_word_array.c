/*
** EPITECH PROJECT, 2019
** my_show_word_array
** File description:
** task03
*/

void my_putchar(char c);

static void my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != 0) {
        my_putchar(str[i]);
        i++;
    }
}

void my_show_word_array(char * const *tab)
{
    int i = 0;

    while (tab[i] != 0) {
        my_putstr(tab[i]);
        my_putchar('\n');
        i = i + 1;
    }
}
