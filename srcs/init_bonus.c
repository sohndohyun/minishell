/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:11 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 01:46:37 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "termcap_bonus.h"

int			ascii_art(void)
{
	int		fd;
	char	*line;

	line = 0;
	if (!(fd = open("ascii_art.txt", O_RDONLY)))
	{
		write(1, "\nError in open\n", 15);
		return (0);
	}
	while (get_next_line(fd, &line) != 0)
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		free(line);
	}
	write(1, line, ft_strlen(line));
	write(1, "\n", 1);
	free(line);
	return (1);
}

int			setup(void)
{
	if (!ascii_art())
		return (0);
	init_term();
	signal(SIGINT, (void *)handle_signal_main);
	signal(SIGQUIT, (void *)handle_signal_main);
	return (1);
}

void		init_term(void)
{
	t_env	*env;

	if (!(env = search_env(g_env, "TERM")))
		env->value = "xterm";
	tgetent(NULL, env->value);
	setupterm(NULL, STDOUT_FILENO, NULL);
	tcgetattr(0, &g_tc->term);
	tcgetattr(0, &g_tc->term_backup);
	g_tc->term.c_lflag = g_tc->term.c_lflag & ~ICANON;
	g_tc->term.c_lflag = g_tc->term.c_lflag & ~ECHO;
	g_tc->term.c_cc[VMIN] = 1;
	g_tc->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_tc->term);
	init_tc();
}

void		init_tc(void)
{
	g_tc->cm = tgetstr("cm", NULL);
	g_tc->ce = tgetstr("ce", NULL);
	g_tc->dl = tgetstr("DL", NULL);
}

void		reinit_termcap(void)
{
	g_tc->rowoffset = 0;
	g_tc->cur_history = NULL;
	g_tc->cur_pos = 0;
}
