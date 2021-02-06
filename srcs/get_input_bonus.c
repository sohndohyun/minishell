/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:24:28 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 03:27:36 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	cursor_win(void)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	g_tc->col = w.ws_col;
	g_tc->row = w.ws_row;
}

char	*ft_strcat(char *dst, const char *src)
{
	int		i;
	int		j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin_middle(char *s1, const char *s2, int div)
{
	char	*str;
	int		l;

	l = ft_strlen(s1) + 1;
	if (!s2)
	{
		str = ft_strdup(s1);
		free((void*)s1);
		return (str);
	}
	if (!(str = (char*)malloc(sizeof(char) * (l + 2))))
		return (NULL);
	ft_strlcpy(str, s1, div);
	str[div] = '\0';
	ft_strcat(str, s2);
	while (div < l)
	{
		str[div] = s1[div - 1];
		div++;
	}
	ft_free_and_null((void **)&s1);
	str[div] = '\0';
	return (str);
}

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

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		i;

	i = ft_strlen(s1);
	while (*s2 && n)
	{
		s1[i] = *s2;
		i++;
		s2++;
		n--;
	}
	s1[i] = '\0';
	return (s1);
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

char	*ft_dups1_frees2(const char *s1, char *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	while (s1[i])
	{
		str[i] = (char)s1[i];
		i++;
	}
	str[i] = '\0';
	free(s2);
	s2 = NULL;
	return (str);
}

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


char	*ft_strjoin_middle2(char *s1, const char *s2, int div)
{
	char	*str;
	int		l;
	char	*tmp;

	if (!s2)
	{
		str = ft_strdup(s1);
		free((void*)s1);
		return (str);
	}
	l = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char*)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	ft_strlcpy(str, s1, div + 1);
	ft_strcat(str, s2);
	tmp = ft_substr(s1, div, ft_strlen(s1) - div);
	ft_strcat(str, tmp);
	free(tmp);
	return (str);
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
	g_tc->copy_cmd = ft_substr(*line, g_tc->cur_pos, ft_strlen(*line) - g_tc->cur_pos);
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
	g_tc->copy_cmd = ft_substr(*line, g_tc->cur_pos, ft_strlen(*line) - g_tc->cur_pos);
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
	g_tc->mod_offset = (ft_strlen(*line) - g_tc->cur_pos + g_tc->plen) / g_tc->col;
	g_tc->currow = g_tc->start_row + g_tc->rowoffset;
}

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

int		get_input(char **line)
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
