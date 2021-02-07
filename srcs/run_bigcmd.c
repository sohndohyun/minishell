/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bigcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 11:55:29 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/07 15:39:16 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_bigcmd(void *value)
{
	t_bigcmd	*cmd;

	cmd = value;
	if (cmd && cmd->cmdstr)
		free(cmd->cmdstr);
	if (cmd)
		free(cmd);
}


static t_list	*find_bigcmd_end(t_list *cmd_list)
{
	t_bigcmd	*cmd;
	int		stack;

	stack = 1;
	cmd_list = cmd_list->next;
	while (cmd_list)
	{
		cmd = cmd_list->content;
		if (cmd->type == CT_BEGIN)
			stack++;
		else if (cmd->type == CT_END)
			if (--stack == 0)
				return (cmd_list);
		cmd_list = cmd_list->next;
	}
	return (cmd_list);
}

void		run_bigcmd_switch_run(char* line)
{
	t_list *token;
	t_list *cmd;

	if (!(token = to_token(line)))
		return ;
	if (!(cmd = to_cmd(token)))
		return ;
	ft_lstclear(&token, free);
	fork_cmd(cmd);
	ft_lstclear(&cmd, free_cmd);
}

void		run_bigcmd(t_list *cmd_list)
{
	t_bigcmd	*cmd;
	int		status;
	int		able;

	able = 1;
	signal(SIGINT, handle_signal_chlid);
	while (cmd_list)
	{
		status = errno;
		cmd = cmd_list->content;
		if (cmd->type == CT_AND)
			able = status == 0 ? 1 : 0;
		else if (cmd->type == CT_OR)
			able = status == 0 ? 0 : 1;
		else if (cmd->type == CT_SEMI)
			able = 1;
		else if (cmd->type == CT_CMD && able)
			run_bigcmd_switch_run(cmd->cmdstr);
		else if (cmd->type == CT_BEGIN && !able)
			cmd_list = find_bigcmd_end(cmd_list);
		cmd_list = cmd_list->next;
	}
}
