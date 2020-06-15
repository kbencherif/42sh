/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** cd_cmd
*/

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include "my.h"
#include "errno.h"
#include "env.h"
#include "built_in.h"
#include "shell.h"

void print_err(char *path)
{
    switch (errno) {
        case EACCES:
            printf("%s: %s.\n", path, "Permission denied");
            break;
        case ENOTDIR:
            printf("%s: %s.\n", path, "Not a directory");
            break;
        case ENOENT:
            printf("%s: %s.\n", path, "No such file or directory");
            break;
    }
}

int cd_cmd(char **path, void *env_list)
{
    char ***env = (char ***) env_list;
    int err_buf = 0;
    char *act_pwd[] = {"PWD", getcwd(NULL, 0)};
    char *old_pwd[] = {"OLD_PWD", my_getenv("PWD", *env)};

    if (*path && my_strcmp(*path, "-"))
        chdir(my_getenv("OLD_PWD", *env));
    else if (!*path)
        chdir(my_getenv("HOME", *env));
    else
        err_buf = chdir(*path);
    my_setenv(old_pwd, env);
    act_pwd[1] = getcwd(NULL, 0);
    my_setenv(act_pwd, env);
    if (err_buf) {
        print_err(*path);
        return MINOR_ERROR;
    }
    return NO_ERROR;
}
