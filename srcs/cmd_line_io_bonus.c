/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line_io_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:35:44 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 23:26:36 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_char(long c, char **line)
{
	char	c2[2];

	c2[0] = c;
	c2[1] = '\0';
	if (*line)
		*line = ft_strjoin_middle(*line, c2, g_tc->cur_pos + 1);
	else
		*line = ft_strdup(c2);
	g_tc->cur_pos++;
}

void	delete_char(char **line)
{
	char	*str;
	int		len;

	if (*line == NULL)
		return ;
	len = ft_strlen(*line);
	if (len == 1 && g_tc->cur_pos == 1)
	{
		ft_free_and_null((void **)line);
		g_tc->cur_pos--;
		return ;
	}
	if (!(str = (char*)ft_calloc(1, sizeof(char) * (len))))
		return ;
	ft_strlcpy(str, *line, g_tc->cur_pos);
	ft_strncat(str, *line + g_tc->cur_pos, len - g_tc->cur_pos);
	ft_free_and_null((void **)line);
	*line = str;
	g_tc->cur_pos--;
}

void	cut_line(char **line)
{
	char	*to_free;

	to_free = NULL;
	if (*line == NULL)
		return ;
	else
		empty_space(ft_strlen(*line) + g_tc->plen);
	to_free = g_tc->copy_cmd;
	g_tc->copy_cmd =
		ft_substr(*line, g_tc->cur_pos, ft_strlen(*line) - g_tc->cur_pos);
	free(to_free);
	to_free = *line;
	*line = ft_substr(*line, 0, g_tc->cur_pos);
	free(to_free);
	g_tc->rowoffset = g_tc->rowoffset - g_tc->mod_offset;
	g_tc->mod_offset = 0;
}

void	copy_line(char **line)
{
	char	*to_free;

	to_free = NULL;
	if (*line == NULL)
		return ;
	to_free = g_tc->copy_cmd;
	g_tc->copy_cmd =
		ft_substr(*line, g_tc->cur_pos, ft_strlen(*line) - g_tc->cur_pos);
	free(to_free);
}

void	paste_line(char **line)
{
	char	*to_free;

	to_free = NULL;
	if (!g_tc->copy_cmd)
		return ;
	if (*line)
	{
		empty_space(ft_strlen(*line) + g_tc->plen);
		to_free = *line;
		*line = ft_strjoin_middle2(*line, g_tc->copy_cmd, g_tc->cur_pos);
		free(to_free);
	}
	else
		*line = ft_strdup(g_tc->copy_cmd);
	g_tc->cur_pos += ft_strlen(g_tc->copy_cmd);
	g_tc->rowoffset = (ft_strlen(*line) + g_tc->plen) / g_tc->col;
	g_tc->mod_offset =
		(ft_strlen(*line) - g_tc->cur_pos + g_tc->plen) / g_tc->col;
	g_tc->currow = g_tc->start_row + g_tc->rowoffset;
}
