/*
** EPITECH PROJECT, 2019
** get_next_line
** File description:
** bonus for multiple fd handling
*/

#include <stdlib.h>
#include "get_next_line.h"

fd_t *init_fd_t(fd_t *fd_buf, int fd)
{
    fd_buf->fd = fd;
    fd_buf->allocd = 0;
    fd_buf->nb_line = 1;
    fd_buf->buf = NULL;
    return fd_buf;
}

void put_in_stack(fd_t **list)
{
    fd_t *element = malloc(sizeof(fd_t));

    if (*list == NULL) {
        *list = element;
        element->next = NULL;
    } else {
        element->next = *list;
        *list = element;
    }
}

void put_in_front(fd_t **fd_list, fd_t *to_push)
{
    fd_t *buf = to_push->next;

    to_push->next = buf->next;
    buf->next = *fd_list;
    *fd_list = buf;
}

void handle_multiple_fd(int fd, fd_t **fd_list)
{
    fd_t *head_buf = *fd_list;

    if (!*fd_list) {
        put_in_stack(fd_list);
        *fd_list = init_fd_t(*fd_list, fd);
        return;
    }
    while (head_buf->next) {
        if (head_buf->next->fd == fd) {
            put_in_front(fd_list, head_buf);
            return;
        }
        head_buf = head_buf->next;
    }
    put_in_stack(fd_list);
    *fd_list = init_fd_t(*fd_list, fd);
}
