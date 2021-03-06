/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:24:28 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 01:06:49 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

void	catch_ctrld(char **line)
{
	char	*line_buf;
	int		flag_exit;

	line_buf = ft_strdup("");
	flag_exit = 1;
	while (get_next_line(STDIN_FILENO, line) == 0)
	{
		line_buf = ft_strjoin_free_s1(line_buf, *line);
		if (**line == '\0' && flag_exit == 1)
		{
			free(*line);
			free(line_buf);
			write(1, "exit\n", 6);
			exit(EXIT_SUCCESS);
		}
		write(1, "  \b\b", 4);
		free(*line);
		flag_exit = 0;
	}
	if (flag_exit == 0)
	{
		free(*line);
		*line = ft_strdup(line_buf);
	}
	free(line_buf);
}

int		get_input(char **line)
{
	catch_ctrld(line);
	if (*line == NULL || ft_strcmp(*line, "") == 0)
	{
		free(*line);
		return (0);
	}
	return (1);
}
