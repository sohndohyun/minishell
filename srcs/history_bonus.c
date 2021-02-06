/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:37:15 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 14:58:22 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	up_history(char **line)
{
	if (g_tc->history == NULL)
		return ;
	if (*line && g_tc->cur_history == NULL)
		g_tc->backup_cmd = ft_dups1_frees2(*line, g_tc->backup_cmd);
	if (g_tc->cur_history == NULL)
		g_tc->cur_history = g_tc->history;
	else if (g_tc->cur_history->next)
		g_tc->cur_history = g_tc->cur_history->next;
	if (*line)
		empty_space(ft_strlen(*line) + g_tc->plen);
	free(*line);
	*line = ft_strdup(g_tc->cur_history->cmd);
	g_tc->cur_pos = ft_strlen(*line);
	g_tc->rowoffset = (g_tc->cur_pos + g_tc->plen) / g_tc->col;
	g_tc->mod_offset = 0;
	g_tc->currow = g_tc->start_row + g_tc->rowoffset;
}

void	down_history(char **line)
{
	if (!g_tc->cur_history)
		return ;
	if (*line)
		empty_space(ft_strlen(*line) + g_tc->plen);
	if (g_tc->cur_history->prev)
	{
		g_tc->cur_history = g_tc->cur_history->prev;
		*line = ft_dups1_frees2(g_tc->cur_history->cmd, *line);
		g_tc->cur_pos = ft_strlen(*line);
	}
	else if (g_tc->backup_cmd)
	{
		*line = ft_dups1_frees2(g_tc->backup_cmd, *line);
		g_tc->cur_history = NULL;
		g_tc->cur_pos = ft_strlen(*line);
	}
	else
	{
		g_tc->cur_pos = 0;
		g_tc->cur_history = NULL;
		ft_free_and_null((void **)line);
	}
	g_tc->rowoffset = (g_tc->cur_pos + g_tc->plen) / g_tc->col;
	g_tc->mod_offset = 0;
	g_tc->currow = g_tc->start_row + g_tc->rowoffset;
}

void	add_cmd_to_history(char *cmd)
{
	t_hist	*new;

	if (!cmd)
		return ;
	if (!(new = ft_calloc(1, sizeof(t_hist))))
		return ;
	new->cmd = ft_strdup(cmd);
	add_history_list(&g_tc->history, new);
}

void	add_history_list(t_hist **begin, t_hist *new)
{
	if (*begin)
	{
		new->next = *begin;
		(*begin)->prev = new;
		*begin = new;
	}
	else
		*begin = new;
}

void	clear_history_list(t_hist **begin)
{
	t_hist	*tmp;
	t_hist	*tmp2;

	tmp = *begin;
	while (tmp)
	{
		ft_free_and_null((void **)&tmp->cmd);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}