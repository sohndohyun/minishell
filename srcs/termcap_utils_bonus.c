/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:36:43 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 14:58:38 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	cursor_win(void)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	g_tc->col = w.ws_col;
	g_tc->row = w.ws_row;
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	empty_space(int len)
{
	int		i;
	int		j;
	char	space[1028];

	g_tc->start_row + g_tc->rowoffset >= g_tc->row ?
		g_tc->start_row = g_tc->currow - g_tc->rowoffset : 0;
	tputs(tgoto(g_tc->cm, g_tc->start_col, g_tc->start_row), 1, putchar_tc);
	tputs(g_tc->ce, 1, putchar_tc);
	i = 0;
	j = 0;
	while (j < len)
	{
		space[i] = ' ';
		i++;
		j++;
		if (i == g_tc->col)
		{
			write(1, space, i);
			i = 0;
		}
	}
	write(1, space, i);
}
