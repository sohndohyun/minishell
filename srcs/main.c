/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:44:15 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/19 21:46:39 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <printf.h>

int main(void)
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
		//write(1, line, ft_strlen(line));
		//write(1, "\n", 1);
		printf("%s\n", line);
		free (line);
	}
	//write(1, line, ft_strlen(line));
	//write(1, "\n", 1);
	printf("%s\n", line);
	free (line);
}
