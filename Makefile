NAME=minishell
CC=gcc
FLAG=-Wall -Wextra -Werror
LIBFT=./libft/libft.a
SRCS= srcs/main.c \
		srcs/init.c \
		srcs/signal_handle.c \
		srcs/print_prompt.c \
		srcs/get_input.c \
		srcs/to_token.c \
		srcs/to_token_utils.c \
		srcs/to_token_utils2.c \
		srcs/to_cmd/to_cmd.c \
		srcs/to_cmd/to_cmd_utils.c \
		srcs/to_cmd/to_cmd_redirection.c \
		srcs/to_cmd/to_cmd_redirection_utils.c \
		srcs/fork_cmd.c \
		srcs/run_cmd.c \
		srcs/run_cmd_utils.c \
		srcs/error.c \
		srcs/env_control.c \
		srcs/utils/utils.c \
		srcs/utils/str_utils.c \
		srcs/utils/lst_utils.c \
		srcs/utils/env_utils.c \
		srcs/builtin/ft_cd.c \
		srcs/builtin/ft_echo.c \
		srcs/builtin/ft_env.c \
		srcs/builtin/ft_exit.c \
		srcs/builtin/ft_export.c \
		srcs/builtin/ft_export_utils.c \
		srcs/builtin/ft_pwd.c \
		srcs/builtin/ft_unset.c \
		srcs/to_cmd/to_bigcmd.c \
		srcs/to_cmd/to_bigcmd_utils.c \
		srcs/to_bigtoken.c \
		srcs/run_bigcmd.c


SRCS_BONUS= srcs/main_bonus.c \
		srcs/init_bonus.c \
		srcs/signal_handle_bonus.c \
		srcs/print_prompt_bonus.c \
		srcs/get_input_bonus.c \
		srcs/cmd_line_io_bonus.c \
		srcs/history_bonus.c \
		srcs/termcap/cursor_bonus.c \
		srcs/termcap/cursor_line_bonus.c \
		srcs/termcap/cursor_word_bonus.c \
		srcs/termcap/termcap_utils_bonus.c \
		srcs/to_token.c \
		srcs/to_token_utils.c \
		srcs/to_token_utils2.c \
		srcs/to_cmd/to_cmd_bonus.c \
		srcs/to_cmd/to_cmd_utils.c \
		srcs/to_cmd/to_cmd_redirection_bonus.c \
		srcs/to_cmd/to_cmd_redirection_utils.c \
		srcs/wildcard/wildcard_bonus.c \
		srcs/wildcard/wildcard_utils_bonus.c \
		srcs/fork_cmd.c \
		srcs/run_cmd.c \
		srcs/run_cmd_utils.c \
		srcs/error.c \
		srcs/env_control.c \
		srcs/utils/utils.c \
		srcs/utils/str_utils.c \
		srcs/utils/lst_utils.c \
		srcs/utils/env_utils.c \
		srcs/builtin/ft_cd.c \
		srcs/builtin/ft_echo.c \
		srcs/builtin/ft_env.c \
		srcs/builtin/ft_exit.c \
		srcs/builtin/ft_export.c \
		srcs/builtin/ft_export_utils.c \
		srcs/builtin/ft_pwd.c \
		srcs/builtin/ft_unset.c \
		srcs/to_cmd/to_bigcmd.c \
		srcs/to_cmd/to_bigcmd_utils.c \
		srcs/to_bigtoken.c \
		srcs/run_bigcmd.c

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
