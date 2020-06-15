##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CC	= 	gcc

SRC	= 	src/main.c	\
		src/init_shell.c	\
		src/env_utils.c		\
		src/read_line/read_line.c	\
		src/read_line/operations.c	\
		src/read_line/input.c	\
		src/parsing/operators_parsing_utils.c	\
		src/parsing/parse_operators.c	\
		src/parsing/parse_command.c \
		src/parsing/exec_command.c	\
		src/parsing/conditionnal_exec_op_parsing.c	\
		src/parsing/quote.c	\
		src/parsing/parse_escape_char.c \
		src/parsing/conditionnal_exec_op_utils.c	\
		src/parsing/globbings.c	\
		src/parsing/parenthesis_error_handling.c	\
		src/parsing/subshell_exec_parsing.c	\
		src/parsing/backticks.c	\
		src/parsing/process_line.c	\
		src/builtin/env_builtin.c	\
		src/builtin/history_cmd.c \
		src/builtin/shell_variables.c	\
		src/builtin/cd_cmd.c	\
		src/builtin/my_exit.c	\
		src/execution/path_handling.c	\
		src/execution/exec_process.c	\
		src/execution/in_out_redirection.c	\
		src/execution/exec_builtin.c	\
		src/execution/backticks.c	\
		src/execution/script.c	\
		src/execution/handle_child_signal.c	\
		src/autocompletion/autocompletion.c	\
		src/autocompletion/check_var.c	\
		src/autocompletion/check_builtin.c	\
		src/autocompletion/display_match.c	\
		src/autocompletion/check_other_possibilities.c	\
		src/autocompletion/copy_to_autocomplete_word.c	\
		src/arraylen.c	\
		src/triplearray.c	\
		src/builtin/remove_alias.c	\
		src/builtin/add_alias.c	\
		src/builtin/array_info.c	\
		src/aliases/change_alias.c	\
		src/builtin/set.c	\
		src/execution/ignoreeof.c	\
		src/builtin/shell_variables_utils.c	\
		src/post_cmd_actions.c	\
		src/aliases/special_aliases.c	\
		src/builtin/which.c	\
		src/builtin/where.c	\
		src/builtin/clean_quote.c	\
		src/parsing/get_word.c	\
		src/builtin/repeat.c	\
		src/builtin/find_alias_loop.c	\

OBJS	=	$(patsubst src/%.c, target/%.o, $(SRC))

NAME 	=	42sh

LDFLAGS	=	-L ./lib/my -lmy

CFLAGS	=	-Wall -Wextra -I ./include -g

TEST	=	./tests/

LIBMY   = lib/my/libmy.a

TEST_OBJ =	$(TEST:.c=.o)

RED=\033[1;31m
GREEN=\033[1;32m
NC=\033[0m

.SILENT:

all: $(NAME)

$(NAME): libmy msg $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) -lncurses
	printf "\n$(GREEN)[✓]$(NC)\x1B[32mExecutable $(NAME) ready !\x1B[37m\n"

target/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -I ./include $(CFLAGS) -o $@
	printf "\e[38;5;27m▒▒\e[0m"

libmy:
	make --no-print-directory -C ./lib/my/

msg:
	@printf "\n\x1B[38;5;27mCompiling $(NAME)...\n\x1b[37m"


test_run: CFLAGS += --coverage
test_run: LDFLAGS += -lcriterion --coverage
test_run: clean $(TEST_OBJ)
	$(CC) -o unit_tests $(TEST_OBJ) $(LDFLAGS)
	./unit_tests

clean:
	make --no-print-directory -C ./lib/my/ clean
	rm -f $(OBJS)
	printf "$(RED)[-]$(NC).o files deleted\n"
	rm -f *.gcno
	rm -f *.gcda

fclean: clean
	make --no-print-directory -C ./lib/my/ fclean
	rm -f $(NAME)
	printf "$(RED)[-]$(NC)Executable $(NAME) deleted\n"
	rm -f *.gcno
	rm -f ./tests/*.gcno
	rm -f *.gcda
	rm -f ./tests/*.gcda
	rm -f ./tests/*.o
	rm -f unit_tests

re: fclean all
