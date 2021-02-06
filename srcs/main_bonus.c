/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:44:15 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/06 21:27:26 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_list	*g_env;

void			run_minishell(char **line, t_list *token, t_list *cmd)
{
	while (1)
	{
		reinit_termcap();
		signal(SIGINT, (void *)handle_signal_main);
		signal(SIGQUIT, (void *)handle_signal_main);
		get_cursor_position(&g_tc->start_col, &g_tc->start_row);
		print_prompt();
		get_cursor_position(&g_tc->col, &g_tc->start_row);
		g_tc->mod_offset = 0;
		if (get_input(line))
		{
			tcsetattr(0, TCSANOW, &g_tc->term_backup);
			add_cmd_to_history(*line);
			if (*line)
			{
				token = to_token(*line);
				cmd = to_cmd(token);
				fork_cmd(cmd);
			}
			ft_lstclear(&token, free);
			ft_lstclear(&cmd, free_cmd);
			tcsetattr(0, TCSANOW, &g_tc->term);
		}
		ft_free_and_null((void **)line);
	}
}

int				main(int argc, char **argv, char **envp)
{
	char		*line;
	t_list		*token;
	t_list		*cmd;
	t_list		*env;
	t_termcap	termcap;

	(void)argc;
	(void)argv;
	env = get_env(envp);
	g_env = env;
	g_tc = &termcap;
	ft_bzero(&termcap, sizeof(t_termcap));
	if (!setup())
		return (1);
	line = NULL;
	token = NULL;
	cmd = NULL;
	run_minishell(&line, token, cmd);
}
