/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** readline
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <term.h>
#include <unistd.h>
#include "read_line.h"

void display_line(edit_line_t *edited_line, char *prompt)
{
    tputs(tgetstr("sc", NULL), 1, &output_char);
    tputs(tgetstr("dl", NULL), 1, &output_char);
    tputs(tgetstr("cr", NULL), 1, &output_char);
    printf("%s%s", prompt, edited_line->line);
    fflush(stdout);
    tputs(tgetstr("rc", NULL), 1, &output_char);
    tputs(tgetstr("nd", NULL), 1, &output_char);
}

void delete_character_term(edit_line_t *line)
{
    if (line->cursor_pos->x > 0) {
        line->line = realloc(line->line, strlen(line->line) + 1);
        line->line[strlen(line->line)] = 0;
        memmove(line->line + line->cursor_pos->x - 1,
                line->line + line->cursor_pos->x,
                strlen(line->line) - line->cursor_pos->x + 1);
        mv_cursor_left(line);
        tputs(tgetstr("im", NULL), 1, &output_char);
        tputs(tgetstr("dc", NULL), 1, &output_char);
        tputs(tgetstr("ei", NULL), 1, &output_char);
    }
}

void insert_character_term(char *prompt, edit_line_t *line, char c)
{
    line->line = realloc(line->line, strlen(line->line) + 2);
    line->line[strlen(line->line) + 1] = 0;
    memmove(line->line + line->cursor_pos->x + 1,
            line->line + line->cursor_pos->x,
            strlen(line->line + line->cursor_pos->x));
    line->line[line->cursor_pos->x] = c;
    line->cursor_pos->x++;
    display_line(line, prompt);
}
