/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:36:24 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 23:54:41 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "wildcard_bonus.h"

int			get_argv_len(t_list *token)
{
	int		i;

	i = 0;
	while (token && !is_type_token(token->content))
	{
		if (is_redirection((token)->content))
		{
			if (to_cmd_redirection_error(token))
				return (-1);
			token = token->next->next;
			continue;
		}
		i++;
		token = token->next;
	}
	return (i);
}

char		**parse_argv(t_list **token, t_cmd *cmd)
{
	char	**argv;
	int		i;
	int		len;

	if (*token == NULL)
		return (NULL);
	i = 0;
	if ((len = get_argv_len(*token)) == -1)
		return (cmd_syntax_error());
	argv = malloc(sizeof(char *) * (len + 1));
	while (*token && !is_type_token((*token)->content))
	{
		if (is_redirection((*token)->content))
		{
			if (!to_cmd_redirection((*token)->content,
						(*token)->next->content, cmd))
				return (print_file_error(i, argv, (*token)->next->content));
			(*token) = (*token)->next->next;
			continue ;
		}
		argv[i++] = ft_strdup((*token)->content);
		(*token) = (*token)->next;
	}
	argv[i] = NULL;
	return (argv);
}

void		parse_type_token(t_list **token, t_cmd *cmd)
{
	char	*temp;

	temp = (*token)->content;
	if (ft_strcmp(temp, "||") == 0)
		cmd->type = CT_OR;
	else if (ft_strcmp(temp, "&&") == 0)
		cmd->type = CT_AND;
	else if (ft_strcmp(temp, "|") == 0)
		cmd->type = CT_PIPE;
	else if (ft_strcmp(temp, ";") == 0)
		cmd->type = CT_SEMI;
	else if (ft_strcmp(temp, "(") == 0)
		cmd->type = CT_BEGIN;
	else
		cmd->type = CT_END;
	(*token) = (*token)->next;
}

int			check_cmd_bucket(t_list *cmd)
{
	int		stack;
	int		cur;

	stack = 0;
	while (cmd)
	{
		cur = ((t_cmd*)cmd->content)->type;
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

t_list		*to_cmd(t_list *token)
{
	t_list	*list;
	t_cmd	*temp;

	list = NULL;
	while (token)
	{
		temp = new_cmd();
		if (is_type_token(token->content))
			parse_type_token(&token, temp);
		else
		{
			if (!(temp->argv = parse_argv(&token, temp)))
				return (clear_cmd(temp, list, token));
			temp->argv = wildcard(temp->argv);
		}
		ft_lstadd_back(&list, ft_lstnew(temp));
	}
	if (!check_cmd_syntax(list))
	{
		ft_lstclear(&token, free);
		return (handle_syntax_error(&list, NULL));
	}
	return (list);
}
