/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** path_handling.c
*/

#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "my.h"
#include "built_in.h"
#include "env.h"
#include "operator_abstract.h"
#include "command.h"
#include "iterators_prototype.h"

define_prototype(command_t);

int search_in_directory(char *cmd_name, char *path)
{
    struct dirent *d_infos;
    DIR *dir = NULL;
    int executable = 0;

    dir = opendir(path);
    while (dir && (d_infos = readdir(dir))) {
        if (dir && my_strcmp(cmd_name, d_infos->d_name)
                && d_infos->d_type != DT_DIR) {
            executable = 1;
        }
    }
    if (dir)
        closedir(dir);
    dir = NULL;
    return executable;
}

int can_access_from_cwd(command_t *cmd)
{
    struct stat info;

    if (!access(cmd->executable_name, F_OK)
        and find_char(cmd->executable_name, '/') >= 0) {
        stat(cmd->executable_name, &info);
        if (!S_ISDIR(info.st_mode) && !access(cmd->executable_name, X_OK)) {
            return true;
        } else {
            write(2, cmd->executable_name, strlen(cmd->executable_name));
            write(2, ": Permission denied.\n", 21);
            return false;
        }
    }
    return -1;
}

bool isnt_builtin(command_t *command)
{
    for (int i = 0; FUNC[i].name; i++)
        if (my_strcmp(FUNC[i].name, command->executable_name))
            return false;
    return true;
}

bool search_path(command_t *cmd, shell_t *shell)
{
    char **paths_tab = my_str_to_word_array(
        my_getenv("PATH", shell->env), ":");
    int found_path = 0;

    for (int i = 0; paths_tab and paths_tab[i]; i++) {
        if (search_in_directory(cmd->executable_name, paths_tab[i])) {
            cmd->path = concate(paths_tab[i], "/");
            return true;
        }
    }
    if ((found_path = can_access_from_cwd(cmd)) >= 0) {
        if (found_path)
            return true;
        return false;
    }
    if (not isnt_builtin(cmd))
        return true;
    write(2, cmd->executable_name, strlen(cmd->executable_name));
    write(2, ": Command not found.\n", 21);
    return false;
}
