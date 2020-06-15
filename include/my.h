/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** include file
*/

#ifndef MY_H
#define MY_H
#include <stdlib.h>
#include <stdbool.h>
#include "command.h"
#include "shell.h"

#define UNUSED __attribute__((unused))

char *my_strdup(char const *src);
char *my_itoa(int number);
char **my_str_to_word_array(char *str, char *delim);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char *s1, char *s2);
char *concate(char *dest, char *src);
int my_getnbr(char const *str);
int my_strncmp(char *s1, char *s2, int n);
int is_alphanumeric(char c);
char **array_cpy(char **array);
char **delete_from_array(char **array, int i);
int find_str(char *str, char *to_find);
int find_char(char *str, char c);
char **array_ncpy(char **array, int len);
char *insert_str(char *cmdptr, char *output, int i);

#define char_ptr char *

#endif
