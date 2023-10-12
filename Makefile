SRCS	=	main.c	parser/parser_redir3.c \
			parser/parser.c parser/input_split.c parser/input_split2.c	\
			parser/parser_delegator.c parser/parser_variable.c	\
			parser/parser_redir.c parser/parser2.c parser/parser_redir2.c	\
			parser/handle_basic.c parser/parser_error.c builtins/echo.c	\
			builtins/pwd.c builtins/cd_utils.c builtins/cd.c	\
			builtins/exec.c  builtins/exec_utils.c builtins/env.c	\
			builtins/export.c builtins/export_utils.c builtins/unset.c	\
			builtins/pipe.c builtins/signal.c builtins/exit.c get_next_line.c

OBJS	= $(SRCS:.c=.o)
NAME	= minishell
LIBFT	= libft/libft.a

CC	= gcc
FLAGS	= -Wall -Wextra -Werror
INCLUDE	= -L libft -lft

all:	$(NAME)

$(NAME): $(OBJS)
	cd libft && $(MAKE)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDE)

clean:
	rm -f $(OBJS) $(B_OBJS)
	cd libft && $(MAKE) clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	cd libft && $(MAKE) fclean

re: fclean all

%.o: %.c
	$(CC) $(FLAGS) -c $<  -o $(<:.c=.o)


.PHONY:	clean fclean re bonus
