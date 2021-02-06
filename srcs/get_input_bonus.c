/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:24:28 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 01:23:09 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "termcap_bonus.h"

void		handle_move_keys(long c, char **line)
{
	if (c == LEFT_ARROW)
		return (move_cursor_left());
	else if (c == RIGHT_ARROW)
		return (move_cursor_right(line));
	else if (c == CTRL_LEFT)
		return (move_prev_word(line));
	else if (c == CTRL_RIGHT)
		return (move_next_word(line));
	else if (c == CTRL_UP)
		return (move_prev_line());
	else if (c == CTRL_DOWN)
		return (move_next_line(line));
	else if (c == HOME)
		return (move_cursor_begin(line));
	else if (c == END)
		return (move_cursor_end(line));
}

void		print_line_sub(long c)
{
	if ((g_tc->cur_pos + g_tc->plen + g_tc->start_col) % g_tc->col == 0 ||
		((g_tc->start_col + g_tc->cur_pos + g_tc->plen + 1) % g_tc->col == 0 &&
		c == BACKSPACE && g_tc->backspace != BACKSPACE) || ((g_tc->cur_pos +
		g_tc->plen + g_tc->start_col - 1) % g_tc->col == 0 && c != BACKSPACE &&
		g_tc->backspace == BACKSPACE))
	{
		c != BACKSPACE ? g_tc->mod_offset -= 1 : 0;
		c == BACKSPACE ? g_tc->mod_offset += 1 : 0;
		if (g_tc->currow >= g_tc->row)
		{
			g_tc->start_row -= 1;
			write(1, "\n", 1);
		}
	}
	g_tc->backspace = c;
	if ((g_tc->lenlen + g_tc->plen + g_tc->start_col) % g_tc->col == 0
		&& c == BACKSPACE)
		write(1, " ", 1);
	tputs(tgoto(g_tc->cm, (g_tc->start_col + g_tc->cur_pos + g_tc->plen)
		% g_tc->col, g_tc->currow - g_tc->mod_offset), 1, putchar_tc);
}

void		print_line(long c, char **line)
{
	tputs(tgoto(g_tc->cm, g_tc->start_col, g_tc->currow - g_tc->rowoffset +
		g_tc->mod_offset), 1, putchar_tc);
	tputs(g_tc->ce, 1, putchar_tc);
	print_prompt();
	if (*line)
		ft_putstr_fd(*line, STDIN_FILENO);
	get_cursor_position(&g_tc->endcol, &g_tc->endrow);
	get_cursor_position(&g_tc->curcol, &g_tc->currow);
	tputs(g_tc->ce, 1, putchar_tc);
	if ((g_tc->start_col + g_tc->lenlen + g_tc->plen) % g_tc->col == 0 ||
		((g_tc->start_col + g_tc->lenlen + g_tc->plen + 1) % g_tc->col == 0 &&
		c == BACKSPACE && g_tc->backspace != BACKSPACE) || ((g_tc->start_col +
		g_tc->lenlen + g_tc->plen - 1) % g_tc->col == 0 && c != BACKSPACE &&
		g_tc->backspace == BACKSPACE))
	{
		c != BACKSPACE && (g_tc->start_col + g_tc->lenlen + g_tc->plen) %
			g_tc->col == 0 ? g_tc->currow += 1 : 0;
		c == BACKSPACE ? g_tc->rowoffset -= 1 : 0;
		c != BACKSPACE ? g_tc->rowoffset += 1 : 0;
		c != BACKSPACE ? g_tc->mod_offset += 1 : 0;
		c == BACKSPACE ? g_tc->mod_offset -= 1 : 0;
	}
	print_line_sub(c);
}

void		handle_keys(long c, char **line)
{
	cursor_win();
	get_cursor_position(&g_tc->curcol, &g_tc->currow);
	g_tc->currow < g_tc->start_row ? g_tc->start_row = g_tc->currow : 0;
	if (ft_isprint(c))
		print_char(c, line);
	else if (c == BACKSPACE && g_tc->cur_pos > 0)
		delete_char(line);
	else if (c == UP_ARROW)
		up_history(line);
	else if (c == DOWN_ARROW)
		down_history(line);
	else if (c == ALT_C)
		return (copy_line(line));
	else if (c == ALT_X)
		cut_line(line);
	else if (c == ALT_V)
		paste_line(line);
	else if (c == LEFT_ARROW || c == RIGHT_ARROW || c == CTRL_LEFT
		|| c == CTRL_RIGHT || c == CTRL_UP || c == CTRL_DOWN || c == HOME
		|| c == END)
		return (handle_move_keys(c, line));
	*line ? g_tc->lenlen = ft_strlen(*line) : 0;
	print_line(c, line);
}

int			get_input(char **line)
{
	int		ret;
	long	c;

	c = 0;
	while ((ret = read(0, &c, sizeof(c))) > 0)
	{
		if (c == '\n')
		{
			if (*line == NULL)
				get_cursor_position(&g_tc->endcol, &g_tc->endrow);
			break ;
		}
		if ((c == EOF_KEY && *line == NULL && (ret = -1) == -1))
			exit(EXIT_SUCCESS);
		handle_keys(c, line);
		c = 0;
	}
	tputs(tgoto(g_tc->cm, g_tc->endcol, g_tc->endrow), 1, putchar_tc);
	write(STDOUT_FILENO, "\n", 1);
	return (1);
}
