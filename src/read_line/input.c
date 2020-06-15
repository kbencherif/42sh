/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** file handling inputs
*/

#include "autocompletion.h"
#include <curses.h>
#include <string.h>
#include <termios.h>
#include <term.h>
#include "my.h"
#include "operator_abstract.h"
#include <stdio.h>
#include <stdbool.h>
#include "read_line.h"
#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

bool is_valid_character(char c)
{
    return c >= ' ' and c <= '~';
}

void mv_cursor_left(edit_line_t *line)
{
    if (line->cursor_pos->x > 0) {
        line->cursor_pos->x--;
        tputs(tgetstr("le", NULL), 1, &output_char);
    }
}

void mv_cursor_right(edit_line_t *line)
{
    if (line->cursor_pos->x < (int) strlen(line->line)) {
        line->cursor_pos->x++;
        tputs(tgetstr("nd", NULL), 1, &output_char);
    }
}

bool get_key_entered(char *prompt,
        char readed_data[3], edit_line_t *line, shell_t *shell)
{
    if (readed_data[0] is ARROWS) {
        if (readed_data[2] is LEFT_ARROW)
            mv_cursor_left(line);
        if (readed_data[2] is RIGHT_ARROW)
            mv_cursor_right(line);
    }
    if (readed_data[0] is DELETE)
        delete_character_term(line);
    if (readed_data[0] is NEW_LINE) {
        putchar('\n');
        shell->eof_nb = 0;
        return true;
    }
    if (readed_data[0] is TAB) {
        autocompletion(prompt, line, shell);
    }
    for (int i = 0; is_valid_character(readed_data[i]); i++)
        insert_character_term(prompt, line, readed_data[i]);
    return false;
}

bool get_special_key_entered(void)
{
    return false;
}
