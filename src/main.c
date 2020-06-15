/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** main file
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <signal.h>
#include <sys/types.h>
#include "command.h"
#include "shell.h"
#include "my.h"
#include "iterators.h"
#include "operator_abstract.h"
#include "read_line.h"
#include "env.h"
#include "parsing.h"
#include "execution.h"

define_iter(char_ptr);

void special_aliases(shell_t *shell, char *escape_char, char *alias);
void clean_quote(char *str);
void post_cmd_actions(shell_t *shell, int cmd_status);

bool hasnt_to_execute(unparsed_cmd_t *cmd, int last_cmd_status)
{
    if (cmd->condition_exec is OR and last_cmd_status is 0)
        return true;
    if (cmd->condition_exec is AND and last_cmd_status isnt 0)
        return true;
    return false;
}

char **replace_shortcut(char **parsed_cmd, shell_t *shell)
{
    for (int i = 0; parsed_cmd[i]; i++) {
        if ((parsed_cmd[i][0] == '~' && strlen(parsed_cmd[i]) == 1))
            parsed_cmd[i] = my_getenv("HOME", shell->env);
        else if (parsed_cmd[i][0] == '~')
            parsed_cmd[i] = concate(my_getenv(
                "HOME", shell->env), parsed_cmd[i] + 1);
        if (not replace_shell_variable(parsed_cmd, shell, i))
            return NULL;
        clean_quote(parsed_cmd[i]);
    }
    return parsed_cmd;
}

int exec_cmds(unparsed_cmd_t **commands, shell_t *shell, char *escape_char)
{
    char **parsed_cmd = NULL;
    int cmd_status = 0;

    for (int i = 0; commands and commands[i]; i++) {
        commands[i]->cmd = execute_backticks(commands[i]->cmd, shell);
        parsed_cmd = replace_shortcut(parse_cmd(commands[i]->cmd), shell);
        if (not parsed_cmd) {
            cmd_status = MINOR_ERROR;
            break;
        } else if (not hasnt_to_execute(commands[i], cmd_status)) {
            cmd_status = exec_cmd(parsed_cmd, commands[i],
                                    shell, escape_char);
        }
        post_cmd_actions(shell, cmd_status);
    }
    return cmd_status;
}

int exec_line(char *lineptr, shell_t *shell, char *escape_char)
{
    int cmd_status = 0;
    unparsed_cmd_t **cmds = NULL;

    if (not line_valid(lineptr))
        return MINOR_ERROR;
    cmds = get_cmds(lineptr);
    for (int i = 0; cmds and cmds[i]; i++) {
        if (cmds[i]->special_exec is PARENTHESIS and cmds[i]->cmd
                and my_strncmp(cmds[i]->cmd, "echo", 4) and cmds[i + 1]
                and cmds[i + 1]->cmd[0] == '|') {
            cmds[i + 1]->cmd = concate(cmds[i]->cmd, cmds[i + 1]->cmd);
            delete_from_array((char **) cmds, i);
        }
    }
    cmd_status = exec_cmds(cmds, shell, escape_char);
    return cmd_status;
}

int main(int argc, UNUSED const char *argv[], char **env)
{
    char *cmdptr = NULL;
    char *prompt = NULL;
    char *escape_char = NULL;
    shell_t *shell = init_shell(env);

    if (argc > 1)
        exec_script(argv[1], shell);
    while (true) {
        special_aliases(shell, escape_char, "precmd");
        prompt = concate(getcwd(NULL, 0), " $> ");
        if (not read_line_stdin(prompt, &cmdptr, shell))
            exit(0);
        process_line(cmdptr, shell);
    }
    return 0;
}
