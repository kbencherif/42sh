/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** directory_manage
*/

#ifndef __DIRECTORY__
#define __DIRECTORY__

#include <dirent.h>

char *stock_directory_info(struct dirent *dir, char *dir_content);
char * read_directory(struct dirent *dir, DIR *dirp);
char **get_dir_content(char *path);

#endif
