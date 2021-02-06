/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_line_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:44:37 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 14:58:14 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	move_prev_line(void)
{
	int		start_col;
	int		start_row;
	int		cur_row;
	int		cur_col;

	start_col = 0;
	start_row = 0;
	cur_row = 0;
	cur_col = 0;
	get_cursor_position(&start_col, &start_row);
	while (g_tc->cur_pos > 0)
	{
		get_cursor_position(&cur_col, &cur_row);
		if (cur_row != start_row && start_col == cur_col)
			break ;
		move_cursor_left();
	}
}

void	move_next_line(char **line)
{
	int		start_col;
	int		start_row;
	int		cur_row;
	int		cur_col;
	int		len;

	start_col = 0;
	start_row = 0;
	cur_row = 0;
	cur_col = 0;
	if (*line == NULL)
		return ;
	len = ft_strlen(*line);
	get_cursor_position(&start_col, &start_row);
	while (g_tc->cur_pos < len)
	{
		get_cursor_position(&cur_col, &cur_row);
		if (cur_row != start_row && start_col == cur_col)
			break ;
		move_cursor_right(line);
	}
}

void	move_cursor_begin(char **line)
{
	int		offset;

	offset = 0;
	if (*line == NULL)
		return ;
	if (g_tc->cur_pos == 0)
		return ;
	while (g_tc->cur_pos > 0)
		move_cursor_left();
}

void	move_cursor_end(char **line)
{
	int		offset;
	int		len;

	offset = 0;
	if (*line == NULL)
		return ;
	len = ft_strlen(*line);
	if (g_tc->cur_pos == len)
		return ;
	while (g_tc->cur_pos < len)
		move_cursor_right(line);
}
