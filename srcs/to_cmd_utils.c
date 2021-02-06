/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:07:06 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 23:07:59 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_type_token(char *str)
{
	return (ft_strcmp(str, "|") == 0 || ft_strcmp(str, ";") == 0
	|| ft_strcmp(str, "&&") == 0 || ft_strcmp(str, "||") == 0
	|| ft_strcmp(str, "(") == 0 || ft_strcmp(str, ")") == 0);
}

void		free_cmd(void *value)
{
	t_cmd	*cmd;

	cmd = value;
	if (cmd && cmd->argv)
		ft_free_2d_arr((void**)cmd->argv);
	if (cmd)
		free(cmd);
}

t_cmd		*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->argv = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->pfd[0][0] = -1;
	cmd->pfd[0][1] = -1;
	cmd->pfd[1][0] = -1;
	cmd->pfd[1][1] = -1;
	cmd->type = CT_CMD;
	return (cmd);
}

int			check_cmd_syntax(t_list *cmd)
{
	int		cur;
	int		next;

	if (!check_cmd_bucket(cmd))
		return (0);
	while (cmd)
	{
		cur = ((t_cmd*)cmd->content)->type;
		next = cmd->next ? ((t_cmd*)cmd->next->content)->type : -1;
		if (cur == CT_CMD && (next == CT_CMD || next == CT_BEGIN))
			return (0);
		else if (cur == CT_PIPE && (next != CT_CMD))
			return (0);
		else if (cur == CT_SEMI && (next == CT_SEMI || next == CT_PIPE
					|| next == CT_AND || next == CT_OR))
			return (0);
		else if ((cur == CT_AND || cur == CT_OR || cur == CT_BEGIN)
				&& (next != CT_CMD && next != CT_BEGIN))
			return (0);
		else if (cur == CT_END &&
				(next == CT_CMD || next == CT_PIPE || next == CT_BEGIN))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

t_list		*clear_cmd(t_cmd *cmd, t_list *cmd_list, t_list *token)
{
	free_cmd(cmd);
	ft_lstclear(&cmd_list, free_cmd);
	ft_lstclear(&token, free);
}
