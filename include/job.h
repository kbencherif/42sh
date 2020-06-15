/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** job header
*/

#ifndef JOB_H
#define JOB_H
#include <sys/wait.h>

typedef struct command command_t;

typedef struct job {
    command_t *command;
    pid_t pid;
    int id;
    int status;
} job_t;

#endif /* JOB_H */
