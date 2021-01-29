NAME=minishell
CC=gcc
FLAG=-Wall -Wextra -Werror
LIBFT=./libft/libft.a
SRCS= srcs/main.c \
		srcs/print_prompt.c \
		srcs/get_input.c \
		srcs/signal_handle.c \
		srcs/to_token.c \
		srcs/to_cmd.c \
		srcs/utils.c \
		srcs/run_cmd.c \
		srcs/fork_cmd.c \
		srcs/ft_cd.c \
		srcs/ft_echo.c \
		srcs/ft_env.c \
		srcs/ft_exit.c \
		srcs/ft_export.c \
		srcs/ft_pwd.c \
		srcs/ft_unset.c \
		srcs/env_utils.c \
		srcs/error.c \
		srcs/to_cmd_redirection.c

HEADER= -I./include/. -I./libft/.
all:
	$(MAKE) -C ./libft
	cp $(LIBFT) _libft.a
	$(CC) $(FLAG) $(HEADER) _libft.a $(SRCS) -o $(NAME)
$(NAME): all
clean:
	$(MAKE) -C ./libft clean
fclean:
	$(MAKE) -C ./libft fclean
	rm -f _libft.a
	rm -f $(NAME)
re: fclean all
