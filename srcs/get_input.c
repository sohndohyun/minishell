/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:24:28 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/21 08:51:18 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_input(char **line)
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
	else if (**line == '\n')
		return (0);
	printf("input : %s$\n", *line);
	free(*line);
	return (1);
}
