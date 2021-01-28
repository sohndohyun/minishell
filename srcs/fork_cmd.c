/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:16:55 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/28 23:20:56 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_cmd_pfd(t_list *cmd_list)
{
	t_cmd	*cmd;
	t_cmd	*bcmd;
	int		pi[2];
	int		cmd_count;

	cmd_count = ft_lstsize(cmd_list);
	bcmd = NULL;
	while (cmd_list)
	{
		cmd = cmd_list->content;
		if (cmd->type == '|')
		{
			pipe(pi);
			bcmd->pfd[1][0] = pi[0];
			bcmd->pfd[1][1] = pi[1];
			cmd->pfd[0][0] = pi[0];
			cmd->pfd[0][1] = pi[1];
		}
		cmd_list = cmd_list->next;
		bcmd = cmd;
	}
}

void fork_cmd(t_list *cmd_list)
{
	t_cmd	*cmd;
	int		status;

	set_cmd_pfd(cmd_list);
	while (cmd_list)
	{
		cmd = cmd_list->content;
		if (!run_cmd_builtin(cmd))
		{
			status = run_cmd(cmd);
			// status 처리
		}
		cmd_list = cmd_list->next;
	}
}
