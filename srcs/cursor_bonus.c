/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:43:05 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 14:58:02 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	move_cursor_left(void)
{
	if (g_tc->cur_pos == 0)
		return ;
	g_tc->cur_pos--;
	(g_tc->start_col + g_tc->cur_pos + g_tc->plen + 1) % g_tc->col == 0 ?
		g_tc->currow -= 1 : 0;
	(g_tc->start_col + g_tc->cur_pos + g_tc->plen + 1) % g_tc->col == 0 ?
		g_tc->mod_offset += 1 : 0;
	tputs(tgoto(g_tc->cm, (g_tc->start_col + g_tc->cur_pos + g_tc->plen) %
		g_tc->col, g_tc->currow), 1, putchar_tc);
}

void	move_cursor_right(char **line)
{
	if (*line == NULL)
		return ;
	if (g_tc->cur_pos == (int)ft_strlen(*line))
		return ;
	g_tc->cur_pos++;
	(g_tc->start_col + g_tc->cur_pos + g_tc->plen) % g_tc->col == 0 ?
		g_tc->currow += 1 : 0;
	(g_tc->start_col + g_tc->cur_pos + g_tc->plen) % g_tc->col == 0 ?
		g_tc->mod_offset -= 1 : 0;
	tputs(tgoto(g_tc->cm, (g_tc->start_col + g_tc->cur_pos + g_tc->plen) %
		g_tc->col, g_tc->currow), 1, putchar_tc);
}


void	get_cursor_position(int *col, int *rows)
{
	int		a;
	int		i;
	char	buf[255];
	int		ret;

	a = 0;
	i = 1;
	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = ft_atoi(&buf[i]) - 1;
			else
				*col = ft_atoi(&buf[i]) - 1;
			a++;
			i += ft_nbr_length(*col) - 1;
		}
		i++;
	}
}
