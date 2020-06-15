/*
** EPITECH PROJECT, 2019
** read line
** File description:
** header
*/

#ifndef READ_LINE_H
#define READ_LINE_H
#include "shell.h"
#include <stdbool.h>
#include "shell.h"

typedef struct position {
    int x;
    int y;
} pos_t;

typedef struct editable_line {
    char *line;
    pos_t *cursor_pos;
} edit_line_t;

bool is_valid_character(char c);
bool read_line_stdin(char *prompt, char **line, shell_t *shell);
bool get_special_key_entered();
bool get_key_entered(char *prompt,
        char readed_data[3], edit_line_t *line, shell_t *shell);
void insert_character_term(char *prompt, edit_line_t *line, char c);
void my_putchar(char c);
int output_char(int c);
void display_line(edit_line_t *edited_line, char *prompt);
void mv_cursor_right(edit_line_t *line);
void delete_character_term(edit_line_t *line);
void mv_cursor_left(edit_line_t *line);
char *get_next_line(int fd);

#define EOT 4
#define ARROWS 27
#define LEFT_ARROW 68
#define RIGHT_ARROW 67
#define DELETE 127
#define NEW_LINE 10
#define TAB 9
#define PASTE 22
#define FLAGS ~(ECHO | ICANON)

#endif /* READ_LINE_H */
