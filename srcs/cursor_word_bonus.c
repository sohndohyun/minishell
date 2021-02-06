/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_word_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:25:25 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 23:26:36 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_prev_word(char **line)
{
	int		is_word;

	if (g_tc->cur_pos == 0)
		return ;
	is_word = 0;
	if (*line == NULL)
		return ;
	g_tc->cur_pos--;
	while (g_tc->cur_pos > 0)
	{
		if (!is_word && (*line)[g_tc->cur_pos] != ' ')
			is_word = 1;
		if (is_word && (*line)[g_tc->cur_pos - 1] == ' ')
			break ;
		move_cursor_left();
	}
}

void	move_next_word(char **line)
{
	int		len;
	int		is_word;

	is_word = 0;
	if (*line == NULL)
		return ;
	len = ft_strlen(*line);
	while (g_tc->cur_pos < len)
	{
		if (!is_word && (*line)[g_tc->cur_pos] != ' ')
			is_word = 1;
		if (is_word && (*line)[g_tc->cur_pos] == ' ')
			break ;
		move_cursor_right(line);
	}
}
