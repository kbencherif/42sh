/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** env header
*/

#ifndef ENV_H
#define ENV_H

char **save_env(char **env);
void replace_existing_field(char *to_set, char ***env, int *i);
char *get_field_name(char *field);
char *my_getenv(char *field, char **env);

#endif /* ENV_H */
