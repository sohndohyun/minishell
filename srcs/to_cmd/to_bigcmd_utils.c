/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bigcmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:50:43 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 22:52:04 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bigcmd		*new_bigcmd(void)
{
	t_bigcmd	*cmd;

	cmd = malloc(sizeof(t_bigcmd));
	cmd->cmdstr = NULL;
	cmd->type = CT_CMD;
	return (cmd);
}

int				is_type_bigtoken(char *str)
{
	return (ft_strcmp(str, ";") == 0
	|| ft_strcmp(str, "&&") == 0 || ft_strcmp(str, "||") == 0
	|| ft_strcmp(str, "(") == 0 || ft_strcmp(str, ")") == 0);
}
