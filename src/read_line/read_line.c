/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** read line
*/

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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

bool manage_eof(shell_t *shell);

int output_char(int c)
{
    write(1, &c, 1);
    return 1;
}

void write_line_on_history(char *line)
{
    char *home_name = getenv("HOME");
    char *history = "/.history_file";
    char *file_name = concate(home_name, history);
    FILE *file = fopen(file_name, "a+");
    time_t actual_time = 0;
    char *time_string = NULL;

    if (!file)
        return;
    actual_time = time(NULL);
    time_string = ctime(&actual_time);
    fwrite((time_string + 11), 1, 5, file);
    fwrite("\t", 1, 1, file);
    fwrite(line, 1, strlen(line), file);
    fwrite("\n", 1, 1, file);
    fclose(file);
}

bool get_term(struct termios *term)
{
    if (tgetent(NULL, getenv("TERM")) < 1)
        return false;
    if (tcgetattr(0, term) is -1)
        return false;
    term->c_lflag = term->c_lflag & FLAGS;
    term->c_cc[VMIN] = true;
    term->c_cc[VTIME] = false;
    if (tcsetattr(0, TCSANOW, term) is -1)
        return false;
    return true;
}

bool line_editing(edit_line_t *line, char *prompt, shell_t *shell)
{
    bool command_entered = false;
    char readed_data[3];

    while (not command_entered) {
        memset(readed_data, 0, 3);
        read(0, &readed_data, 3);
        if (readed_data[0] is EOT)
    		return manage_eof(shell);
        if (not (command_entered = get_special_key_entered()))
            command_entered = get_key_entered(prompt, readed_data, line,
                    shell);
    }
    return true;
}

bool read_line_stdin(char *prompt, char **line, shell_t *shell)
{
    struct termios *term = malloc(sizeof(struct termios));
    edit_line_t edit_line = {strdup(""), malloc(sizeof(pos_t))};
    size_t size = 0;

    if (not isatty(0)) {
        if (getline(line, &size, stdin) is -1)
            return false;
        (*line)[strlen(*line) - 1] = 0;
        return true;
    }
    *edit_line.cursor_pos = (pos_t) {0, 0};
    if (not get_term(term))
        return false;
    printf("%s", prompt);
    fflush(stdout);
    if (not line_editing(&edit_line, prompt, shell))
        return false;
    *line = edit_line.line;
    write_line_on_history(*line);
    return true;
}
