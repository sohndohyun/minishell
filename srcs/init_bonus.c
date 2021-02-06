/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:11 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 23:26:36 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			setup(void)
{
	if (!ascii_art())
		return (0);
	init_term();
	signal(SIGINT, (void *)handle_signal_main);
	signal(SIGQUIT, (void *)handle_signal_main);
	return (1);
}

t_list		*get_env(char **envp)
{
	int		pos;
	t_env	*env;
	t_list	*envs;

	envs = 0;
	while (*envp)
	{
		env = (t_env *)malloc(sizeof(t_env));
		pos = ft_strchr(*envp, '=') - *envp;
		env->key = ft_substr(*envp, 0, pos);
		env->value = ft_substr(*envp, pos + 1, ft_strlen(*envp) - pos - 1);
		ft_lstadd_back(&envs, ft_lstnew(env));
		envp++;
	}
	if (search_env(envs, "OLDPWD") == NULL)
	{
		env = (t_env *)malloc(sizeof(t_env));
		env->key = ft_strdup("OLDPWD");
		env->value = NULL;
		ft_lstadd_back(&envs, ft_lstnew(env));
	}
	return (envs);
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
