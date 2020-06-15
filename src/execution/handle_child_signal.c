/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** signal from child handling
*/

#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

void handle_child_signals(int status)
{
    switch (WTERMSIG(status)) {
        case SIGSEGV:
            write(2, "Segmentation fault", 18);
            if (WCOREDUMP(status))
                write(2, " (core dumped)", 14);
            write(2, "\n", 1);
            break;
        case SIGFPE:
            write(2, "Floating exception", 18);
            if (WCOREDUMP(status))
                write(2, " (core dumped)", 14);
            write(2, "\n", 1);
            break;
    }
}
