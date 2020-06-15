/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** parsing
*/

#ifndef PARSING_H
#define PARSING_H
#include "command.h"

char *parse_word(char *cmd, int *i);
int get_nb_words(char *cmd);
char *get_word(char *cmd, int *i, int *j);
char *get_escape_char(char **cmdptr);
void change_escape_char(char ***arguments, char *escape_char);
int get_redirection(char **argv, int i);
char **concate_double_operators(char **cmd);
void get_operator_and_arg(command_t *command, char **argv);
bool is_redirect(char *c);
bool is_pipe(char *c);
char *erase_space_or_tab(char *cmd, int i);
char **parse_cmd(char *cmd);
char *clean_line(char *cmd);
bool is_empty_command(char **cmd_line);
int count_operators(char *line);
bool isnt_valid_typed_line(char *line);
int find_next_op(char *str);
int replace_globbings(command_t *command);
bool backtick_unmatched(char *command);
bool line_valid(char *line);
unparsed_cmd_t **get_cmds(char *lineptr);
unparsed_cmd_t **get_chained_commands(unparsed_cmd_t **commands,
                                        char *cmd_part, int exec,
                                        int *j);
char **replace_shell_variable(char **parsed_cmd,
                                shell_t *shell,
                                int i);
unparsed_cmd_t **get_spec_cond_exec_op(cmd_list_t **cmd_list);
char *delete_backticked_cmd(char *line);
char **get_backticked_cmd(char *line);
void process_line(char *line, shell_t *shell);
bool cmd_not_valid(char **command);

#endif /* PARSING_H */
