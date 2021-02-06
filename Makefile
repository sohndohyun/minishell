NAME=minishell
CC=gcc
FLAG=-Wall -Wextra -Werror
LIBFT=./libft/libft.a
SRCS= srcs/main.c \
		srcs/print_prompt.c \
		srcs/get_input.c \
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
		srcs/ft_export_utils.c \
		srcs/ft_pwd.c \
		srcs/ft_unset.c \
		srcs/env_utils.c \
		srcs/env_control.c \
		srcs/error.c \
		srcs/init.c \
		srcs/lst_utils.c \
		srcs/to_cmd_redirection.c \
		srcs/wildcard.c

SRCS_BONUS= srcs/main_bonus.c \
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
		srcs/ft_export_utils.c \
		srcs/ft_pwd.c \
		srcs/ft_unset.c \
		srcs/env_control.c \
		srcs/env_utils.c \
		srcs/error.c \
		srcs/lst_utils.c \
		srcs/to_cmd_redirection.c \
		srcs/wildcard.c \
		srcs/init_bonus.c \
		srcs/history_bonus.c \
		srcs/termcap_utils_bonus.c \
		srcs/cursor_word_bonus.c \
		srcs/cursor_line_bonus.c \
		srcs/cursor_bonus.c \
		srcs/cmd_line_io_bonus.c

OBJS			= ${SRCS:.c=.o}
OBJS_BONUS		= ${SRCS_BONUS:.c=.o}


HEADER= -I./include/. -I./libft/.

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	cp $(LIBFT) _libft.a
	$(CC) $(FLAG) $(HEADER) _libft.a $^ -o $(NAME)


%.o: %.c
	$(CC) $(FLAG) $(HEADER) -o $@ -c $<

bonus: $(OBJS_BONUS)
	$(MAKE) -C ./libft
	cp $(LIBFT) _libft.a
	$(CC) $(FLAG) -lncurses $(HEADER) _libft.a $^ -o $(NAME)

clean:
	$(MAKE) -C ./libft clean
	rm -f $(OBJS) $(OBJS_BONUS)

fclean:
	$(MAKE) -C ./libft fclean
	rm -f _libft.a
	rm -f $(NAME)
	rm -f $(OBJS) $(OBJS_BONUS)

re: fclean all
