##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Lib Makefile
##

SRC     =	my_compute_power_rec.c  	\
			my_put_u_nbr.c	\
			my_getnbr.c     		\
			get_u_nb_size.c     		\
			my_put_uns_nbr.c	\
			my_fput_uns_nbr.c	\
			my_isneg.c      		\
			my_putchar.c			\
			my_put_nbr.c			\
			my_putstr.c			\
			my_revstr.c			\
			my_show_word_array.c	\
			my_strcpy.c			\
			my_strdup.c			\
			my_strlen.c			\
			my_strstr.c	\
			my_strncpy.c			\
			my_str_to_word_array.c	\
			my_swap.c			\
			my_calloc.c	\
			my_printf/store_options.c	\
			my_printf/my_printf.c	\
			my_printf/print3.c	\
			my_printf/print2.c	\
			my_printf/print.c	\
			my_printf/get_options.c	\
			my_printf/modifiers.c \
			get_next_line.c	\
			multiple_fd.c	\
			my_realloc.c	\
			concate.c	\
			my_strcmp.c	\
			my_strncmp.c	\
			is_alphanumeric.c	\
			my_itoa.c	\
			free_double_array.c	\
			my_fputchar.c	\
			my_fput_u_nbr.c	\
			my_fput_nbr.c	\
			my_fputstr.c	\
			my_fput_uns_nbr.c	\
			my_fprintf/fprint.c	\
			my_fprintf/fprint2.c	\
			my_fprintf/fprint3.c	\
			my_fprintf/fmodifiers.c	\
			my_fprintf/my_fprintf.c	\
			my_memset.c \
			array_cpy.c	\
			clean_line.c	\
			my_strndup.c	\
			find_str.c	\
			find_char.c	\
			delete_from_array.c	\
			array_ncpy.c	\
			is_alpha.c	\

OBJ	=	$(SRC:.c=.o)

NAME =	libmy.a

CFLAGS	=	-Wall -Wextra -I ./include -g

RED=\033[1;31m
GREEN=\033[1;32m
NC=\033[0m

.SILENT:

all: $(NAME)

$(NAME): lib $(OBJ)
	ar rc $(NAME) $(OBJ)
	printf "\n$(GREEN)[✓]$(NC)\x1B[32mLib $(NAME) built !\n\x1B[37m"

lib:
	printf "$(NC)\x1B[32mCompiling library $(NAME)...\n\x1b[37m"

%.o : %.c
	printf "$(GREEN)▒\e[0m"
	gcc -o $@ -c -I ./include $(CFLAGS) $^

clean:
	rm -f $(OBJ)
	printf "$(RED)[-]$(NC)Library .o files deleted\x1B[37m\n"

fclean: clean
	rm -f $(NAME)
	printf "$(RED)[-]$(NC)Lib $(NAME) deleted\x1B[37m\n"

re: fclean all
