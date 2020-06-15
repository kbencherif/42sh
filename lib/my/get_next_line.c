/*
** EPITECH PROJECT, 2019
** get_next_line.c
** File description:
** main file
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char *my_realloc(char *str, int size)
{
    char *new_str = malloc(size);
    int i = 0;

    if (!new_str) {
        return NULL;
    }
    if (!str) {
        str = malloc(size);
        free(new_str);
        return str;
    }
    while (str[i] != '\0') {
        new_str[i] = str[i];
        i = i + 1;
    }
    new_str[i] = '\0';
    free(str);
    return new_str;
}

char *read_line(char *buf, int fd, int allocd)
{
    int checker = 0;
    int size = READ_SIZE;
    char *readed = malloc(READ_SIZE + 1);

    checker = read(fd, readed, READ_SIZE);
    if (checker == -1 || checker == 0) {
        free(readed);
        free(buf);
        return NULL;
    }
    readed[checker] = 0;
    for (int i = 0; readed[i]; i++) {
        buf[allocd - size] = readed[i];
        size--;
    }
    buf[allocd - size] = 0;
    free(readed);
    return buf;
}

int count_line(char *buf)
{
    int number_line = 0;

    if (!buf)
        return 0;
    for (int i = 0; buf[i]; i++)
        if (buf[i] == '\n')
            number_line++;
    return number_line;
}

char *format_line(char *buf, int nb_line, char *line)
{
    int j = 0;
    int i = 0;
    int buf_line = nb_line;

    for (; buf_line - 1; i++)
        if (buf[i] == '\n') {
            buf_line--;
        }
    j = i;
    for (; buf[j] && buf[j] != '\n'; j++);
    line = malloc(j - i + 1);
    j = 0;
    for (; buf[i] && buf[i] != '\n'; i++, j++)
        line[j] = buf[i];
    line[j] = 0;
    return line;
}

char *get_next_line(int fd)
{
    static fd_t *fd_buf = NULL;
    char *line = NULL;

    if (fd == -1)
        return NULL;
    if (!fd_buf || fd_buf->fd != fd)
        handle_multiple_fd(fd, &fd_buf);
    while (count_line(fd_buf->buf) < fd_buf->nb_line) {
        fd_buf->buf = my_realloc(fd_buf->buf, fd_buf->allocd + READ_SIZE + 1);
        if (!fd_buf->buf)
            return NULL;
        fd_buf->allocd += READ_SIZE;
        fd_buf->buf = read_line(fd_buf->buf, fd_buf->fd, fd_buf->allocd);
        if (!fd_buf->buf)
            return NULL;
    }
    fd_buf->nb_line++;
    return format_line(fd_buf->buf, fd_buf->nb_line - 1, line);
}
