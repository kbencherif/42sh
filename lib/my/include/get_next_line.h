/*
** EPITECH PROJECT, 2019
** get_next_line.h
** File description:
** get_next_line .h file
*/

#ifndef G_N_L_
#define G_N_L_

#ifndef READ_SIZE
#define READ_SIZE (1)
#endif

typedef struct fd
{
    int fd;
    int allocd;
    int nb_line;
    char *buf;
    struct fd *next;
} fd_t;

void handle_multiple_fd(int fd, fd_t **fd_buf);
char *get_next_line(int fd);
int count_line(char *buf);

#endif
