/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 03:13:55 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/29 17:13:59 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_redirection(char *str)
{
	return (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0 ||
		ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0);
}

int		to_cmd_redirection_error(t_list *token)
{
	if(!token->next)
		return (1);
	token = token->next;
	if (is_redirection(token->content) ||
		ft_strcmp(token->content, "|") == 0 ||
		ft_strcmp(token->content, ";") == 0)
		return (1);
	return (0);
}

int		to_cmd_redirection(char *type, char *value, t_cmd *cmd)
{
	if (!type || !value)
		return (0);
	if (ft_strcmp(type, "<") == 0)
	{
		cmd->fd_in = open(value, O_RDONLY);
		if (cmd->fd_in < 0)
			return (0);
		return (1);
	}
	else if (ft_strcmp(type, ">") == 0)
	{
		cmd->fd_out = open(value, O_WRONLY | O_CREAT, 0644);
		if (cmd->fd_out < 0)
			return (0);
		return (1);
	}
	else if (ft_strcmp(type, ">>") == 0)
	{
		cmd->fd_out = open(value, O_WRONLY | O_APPEND, 0644);
		if (cmd->fd_out < 0)
			return (0);
		return (1);
	}
	else
	{
		// not finished yet.
		return (0);
	}
	return (0);
}