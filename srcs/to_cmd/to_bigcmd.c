/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bigcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 03:31:05 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/07 22:51:04 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_bigcmd_bucket(t_list *cmd)
{
	int			stack;
	int			cur;

	stack = 0;
	while (cmd)
	{
		cur = ((t_bigcmd*)cmd->content)->type;
		if (cur == CT_BEGIN)
			stack++;
		else if (cur == CT_END)
		{
			if (--stack < 0)
				return (0);
		}
		cmd = cmd->next;
	}
	if (stack != 0)
		return (0);
	return (1);
}

int				check_bigcmd_syntax_loop(t_list *cmd,
					int cur, int next, int flag)
{
	while (cmd)
	{
		cur = ((t_bigcmd*)cmd->content)->type;
		next = cmd->next ? ((t_bigcmd*)cmd->next->content)->type : -1;
		if (flag && (cur == CT_AND || cur == CT_END || cur == CT_OR))
			return (0);
		else if (cur == CT_CMD && (next == CT_CMD || next == CT_BEGIN))
			return (0);
		else if (cur == CT_SEMI && (next == CT_SEMI
					|| next == CT_AND || next == CT_OR))
			return (0);
		else if ((cur == CT_AND || cur == CT_OR || cur == CT_BEGIN)
				&& (next != CT_CMD && next != CT_BEGIN))
			return (0);
		else if (cur == CT_END && (next == CT_CMD || next == CT_BEGIN))
			return (0);
		if (cur == CT_CMD && ((t_bigcmd*)cmd->content)->cmdstr[0] == '|')
			return (0);
		cmd = cmd->next;
		flag = 0;
	}
	return (1);
}

static int		check_bigcmd_syntax(t_list *cmd)
{
	if (!check_bigcmd_bucket(cmd))
		return (0);
	return (check_bigcmd_syntax_loop(cmd, 0, 0, 1));
}

void			parse_type_bigtoken(t_list **token, t_bigcmd *cmd)
{
	char		*temp;

	temp = (*token)->content;
	if (ft_strcmp(temp, "||") == 0)
		cmd->type = CT_OR;
	else if (ft_strcmp(temp, "&&") == 0)
		cmd->type = CT_AND;
	else if (ft_strcmp(temp, ";") == 0)
		cmd->type = CT_SEMI;
	else if (ft_strcmp(temp, "(") == 0)
		cmd->type = CT_BEGIN;
	else
		cmd->type = CT_END;
}

t_list			*to_bigcmd(t_list *bigtoken)
{
	t_list		*list;
	t_bigcmd	*temp;
	t_list		*save;

	save = bigtoken;
	list = NULL;
	while (bigtoken)
	{
		temp = new_bigcmd();
		if (is_type_bigtoken(bigtoken->content))
			parse_type_bigtoken(&bigtoken, temp);
		else
			temp->cmdstr = ft_strdup(bigtoken->content);
		ft_lstadd_back(&list, ft_lstnew(temp));
		bigtoken = bigtoken->next;
	}
	if (!check_bigcmd_syntax(list))
	{
		ft_lstclear(&save, free);
		return (handle_cmd_syntax_error(&list, free_bigcmd));
	}
	return (list);
}
