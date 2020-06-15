/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** task02
*/


#ifndef MY_H_
#define MY_H_

#include "my_struct.h"

int my_compute_power_rec(int nb, int power);
int my_getnbr(char const *str);
int my_isneg(int nb);
void my_putchar(char c);
void my_put_nbr(int nb);
void my_put_u_nbr(int nb);
void my_fput_nbr(FILE *stream, int nb);
void my_fput_u_nbr(FILE *stream, int nb);
void my_putstr(char const *str);
char *my_revstr(char *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char *s1, char *s2);
char *my_strcpy(char *dest, char const *src);
int my_strlen(char const *str);
char *my_strncat(char *dest, char const *src, int nb);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strdup(char const *src);
char *my_calloc(int size);
int get_width(string_t *str_s);
int get_flags(string_t *str_s);
int get_type(string_t *str_s);
int get_type2(string_t *str_s);
int print_start(string_t *str_s, int j);
data_stocker_t op_parser(string_t *str_s);
data_stocker_t put_in_struct(int data, data_stocker_t data_stock);
data_stocker_t put_width(int data, data_stocker_t data_stock);
int my_printf(const char *str, ...);
int print_int(va_list ap, data_stocker_t data_stocker);
int hash_flag(data_stocker_t data_stocker);
int print_octal(va_list ap, data_stocker_t data_stocker);
int print_char(va_list ap, data_stocker_t data_stocker);
int print_str(va_list ap, data_stocker_t data_stocker);
int get_nb_size(int arg);
int print_str_ss(va_list ap, data_stocker_t data_stocker);
int print_u_int(va_list ap, UNUSED data_stocker_t data_stocker);
int print_hexa_x(va_list ap, data_stocker_t data_stocker);
int print_hexa_xx(va_list ap, data_stocker_t data_stocker);
int print_binary(va_list ap, data_stocker_t data_stocker);
int apply_width(int size, data_stocker_t data_stocker, int pos);
int plus_space_flag(data_stocker_t data_stocker);
int get_precision(string_t *str_s);
data_stocker_t put_precision(int data, data_stocker_t data_stocker);
int print_percent( UNUSED va_list ap, data_stocker_t data_stocker);
int print_address(va_list ap, data_stocker_t data_stocker);
void my_put_uns_nbr(unsigned int nb);
int get_u_nb_size(unsigned int arg);
int print_float(va_list ap, data_stocker_t data_stocker);
int my_fprintf(FILE *stream, const char *str, ...);
int fprint_address(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_float(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_binary(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_hexa_xx(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_hexa_x(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_u_int(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_str_ss(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_str(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_char(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_octal(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_int(va_list ap, data_stocker_t data_stocker, FILE* stream);
int fprint_start(string_t *str_s, int j, FILE* stream);
int fprint_percent(UNUSED va_list ap, UNUSED data_stocker_t data_stocker,
                FILE *stream);
char *clean_line(char *cmd);
int fhash_flag(data_stocker_t data_stocker, FILE *stream);
int fplus_space_flag(data_stocker_t data_stocker, FILE *stream);
void my_fput_uns_nbr(FILE *stream, unsigned int nb);
int fapply_width(int size, data_stocker_t data_stocker, int pos, FILE *stream);
int fprint_int(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_char(va_list ap, data_stocker_t data_stocker, FILE *stream);
int fprint_start(string_t *str_s, int j, FILE *stream);
void my_fputstr(FILE *stream, char const *str);
void my_fputchar(FILE *stream, char c);
int is_alphanumeric(char c);

static const data_getter_t ARRAY[] = {
    get_flags,
    get_width,
    get_precision,
    get_type,
    get_type2,
    NULL
};

#endif
