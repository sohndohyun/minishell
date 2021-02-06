/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd_redirection_util.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:52:08 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/06 21:53:05 by dsohn            ###   ########.fr       */
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
	if (!token->next)
		return (1);
	token = token->next;
	if (is_redirection(token->content) ||
		ft_strcmp(token->content, "|") == 0 ||
		ft_strcmp(token->content, ";") == 0)
		return (1);
	return (0);
}
