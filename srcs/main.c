/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:44:15 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/07 16:43:30 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "utils.h"
#include <stdio.h>
t_list	*g_env;

void	print_bigcmd(t_list *cmd)
{
	t_bigcmd *bcmd;

	while (cmd)
	{
		bcmd = cmd->content;
		printf("type: %d\n", bcmd->type);
		if (bcmd->cmdstr)
			printf("str: %s\n", bcmd->cmdstr);
		cmd = cmd->next;
	}
}

void	run_minishell(char **line, t_list *token, t_list *cmd)
{
	while (1)
	{
		signal(SIGINT, (void *)handle_signal_main);
		signal(SIGQUIT, (void *)handle_signal_main);
		print_prompt();
		if (!get_input(line))
			continue ;
		if (!(token = to_bigtoken(*line)))
			continue;
		if (!(cmd = to_bigcmd(token)))
		{
			ft_free_and_null((void **)line);
			continue ;
		}
		ft_lstclear(&token, free);
		run_bigcmd(cmd);
		ft_lstclear(&cmd, free_bigcmd);
		ft_free_and_null((void **)line);
	} 
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*token;
	t_list	*cmd;
	t_list	*env;

	(void)argc;
	(void)argv;
	if (!setup())
		return (1);
	env = get_env(envp);
	g_env = env;
	token = NULL;
	cmd = NULL;
	run_minishell(&line, token, cmd);
}
