NAME=minishell
CC=gcc
FLAG=-Wall -Wextra -Werror
LIBFT=./libft/libft.a
SRCS= srcs/main.c
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