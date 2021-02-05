NAME=minishell
CC=gcc
FLAG=-Wall -Wextra -Werror -lncurses
LIBFT=./libft/libft.a
SRCS= srcs/main_bonus.c \
		srcs/cursor.c \
		srcs/print_prompt_bonus.c \
		srcs/get_input_bonus.c \
		srcs/signal_handle.c \
		srcs/to_token.c \
		srcs/to_token_utils.c \
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
		srcs/env_utils2.c \
		srcs/lst_utils.c \
		srcs/to_cmd_redirection.c \
		srcs/wildcard.c

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
