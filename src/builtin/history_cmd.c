/*
** EPITECH PROJECT, 2020
** history_cmd
** File description:
** .c
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"

int my_history(UNUSED char **arg, void *env_list)
{
    UNUSED char ***env = (char ***) env_list;
    char *home_name = getenv("HOME");
    char *history = "/.history_file";
    char *file_name = concate(home_name, history);
    FILE *file = fopen(file_name, "r");
    int bytes_read = 0;
    char *buffer = NULL;
    size_t size = 0;

    if (!file)
        return (1);
    for (int nb = 1; bytes_read != -1;) {
        bytes_read = getline(&buffer, &size, file);
        if (bytes_read != -1) {
            printf("\t%d  ", nb);
            printf("%s", buffer);
            nb++;
        }
    }
    fclose(file);
    return (0);
}
