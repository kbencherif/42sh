/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** include for my struct type def
*/

#ifndef STRUCT_H_
#define STRUCT_H_
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include "my_maccro.h"
#include "my.h"

typedef struct data_stocker {
    int width;
    int precision;
    int hash;
    int zero;
    int space;
    int minus;
    int plus;
    int type;
} data_stocker_t;

typedef struct string {
    char const *str;
    int i;
} string_t;

typedef int (*data_getter_t) (string_t *str_s);
typedef int (*print_func_t) (va_list ap, data_stocker_t data_stocker);
typedef int (*fprint_func_t) (va_list ap, data_stocker_t data_stocker,
                            FILE *stream);

typedef struct t_fmodifiers {
    int type;
    fprint_func_t fprint_func;
} t_fmodifiers_t;

typedef struct t_modifiers {
    int type;
    print_func_t print_func;
} t_modifiers_t;

typedef struct corner
{
    int x;
    int y;
} corner_t;

typedef struct square
{
    corner_t tl_corner;
    corner_t tr_corner;
    corner_t bl_corner;
    corner_t br_corner;
} square_t;

#endif /*STRUCT_H*/
