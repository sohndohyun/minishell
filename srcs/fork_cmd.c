/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:16:55 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/02 00:37:46 by hyeonski         ###   ########.fr       */
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
	int		save_in;
	int		save_out;

	set_cmd_pfd(cmd_list);
	signal(SIGINT, handle_signal_chlid);
	while (cmd_list)
	{
		save_in = -1;
		save_out = -1;
		cmd = cmd_list->content;
		if (cmd->fd_in != 0)
		{
			save_in = dup(0);
			dup2(cmd->fd_in, 0);
		}
		if (cmd->fd_out != 1)
		{
			save_out = dup(1);
			dup2(cmd->fd_out, 1);
		}
		if (is_cmd_builtin(cmd->argv[0]))
			status = run_cmd_builtin(cmd);
		else
			status = run_cmd(cmd, run_cmd_execve);
		if (save_in != -1)
		{
			close(cmd->fd_in);
			dup2(save_in, 0);
		}
		if (save_out != -1)
		{
			close(cmd->fd_out);
			dup2(save_out, 1);
		}
		cmd_list = cmd_list->next;
	}
	errno = status;
}
