/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:16:55 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/25 22:26:04 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fork_cmd(t_list *cmd_list)
{
	t_list	*it;
	t_cmd	*cmd;
	t_cmd	*bcmd;
	int		pi[2];
	pid_t	pid;
	int		cmd_count;
	int		status;

	cmd_count = ft_lstsize(cmd_list);
	bcmd = NULL;
	it = cmd_list;
	while (it)
	{
		cmd = it->content;
		if (cmd->type == '|')
		{
			pipe(pi);
			bcmd->pfd[1][0] = pi[0];
			bcmd->pfd[1][1] = pi[1];
			cmd->pfd[0][0] = pi[0];
			cmd->pfd[0][1] = pi[1];
		}
		it = it->next;
		bcmd = cmd;
	}
	it = cmd_list;
	while (it)
	{
		cmd = it->content;
		if (!(pid = fork()))
		{
			if (cmd->pfd[0][0] != -1)
				dup2(cmd->pfd[0][0], 0);
			if (cmd->pfd[1][0] != -1)
				dup2(cmd->pfd[1][1], 1);
			run_cmd(cmd);
		}
		if (cmd->pfd[0][0] != -1)
			close(cmd->pfd[0][0]);
		if (cmd->pfd[1][0] != -1)
			close(cmd->pfd[1][1]);
		waitpid(pid, &status, 0);
		//status 처리 ???
		it = it->next;
	}
}
