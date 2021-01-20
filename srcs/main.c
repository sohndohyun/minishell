/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:44:15 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/20 12:00:32 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ascii_art(void)
{
	int fd;
	char *line;

	line = 0;
	if (!(fd = open("ascii_art.txt", O_RDONLY)))
	{
		write(1, "\nError in open\n", 15);
		return (0);
	}
	while (get_next_line(fd, &line) != 0)
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		free (line);
	}
	write(1, line, ft_strlen(line));
	write(1, "\n", 1);
	free (line);
	return (1);
}

void	print_prompt(void)
{
	write(1, "minishell$ ", 12);
}

void	get_input(char **line)
{
	if (!get_next_line(STDIN_FILENO, line))
	{
		if (**line == '\0')
		{
			write(1, "\b ", 2);
			free(*line);
			write(1, "exit\n", 6);
			exit(0);
		}
	}
	printf("input : %s$\n", *line);
	free(*line);
}

int		main(void)
{
	char *line;
	
	if (!ascii_art())
		return (1);
	while (1)
	{
		print_prompt();
		get_input(&line);
	}
}
