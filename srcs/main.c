/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:44:15 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/06 15:01:16 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_env;

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
	while (1)
	{
		signal(SIGINT, (void *)handle_signal_main);
		signal(SIGQUIT, (void *)handle_signal_main);
		print_prompt();
		if (!get_input(&line))
			continue ; //nothing input!
		if (!(token = to_token(line)) || !(cmd = to_cmd(token)))
			continue ; //syntax error!
		free(line);
		ft_lstclear(&token, free);
		fork_cmd(cmd);
		ft_lstclear(&cmd, free_cmd);
	}
}
