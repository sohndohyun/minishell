/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:36:24 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 17:12:34 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_type_token(char *str)
{
	return (ft_strcmp(str, "|") == 0 || ft_strcmp(str, ";") == 0
	|| ft_strcmp(str, "&&") == 0 || ft_strcmp(str, "||") == 0
	|| ft_strcmp(str, "(")  == 0 || ft_strcmp(str, ")") == 0);
}

int		get_argv_len(t_list *token)
{
	int i;

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

char	**parse_argv(t_list **token, t_cmd *cmd)
{
	char	**argv;
	int		i;
	int		len;

	if (*token == NULL)	
		return (NULL);
	i = 0;
	len = get_argv_len(*token);
	if (len == -1)
	{
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		errno = 258;
		return (NULL);
	}
	argv = malloc(sizeof(char *) * (len + 1));
	while (*token && !is_type_token((*token)->content))
	{
		if (is_redirection((*token)->content))
		{
			if (!to_cmd_redirection((*token)->content, (*token)->next->content, cmd))
			{
				while (--i >= 0)
					free(argv[i]);
				free(argv);
				errno = 2;
				print_error((*token)->next->content, 2, strerror(2));
				return (NULL);
			}
			(*token) = (*token)->next->next;
			continue;
		}
		argv[i] = ft_strdup((*token)->content);
		i++;
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

void	free_cmd(void *value)
{
	t_cmd *cmd;

	cmd = value;
	if (cmd && cmd->argv)
		ft_free_2d_arr((void**)cmd->argv);
	if (cmd)
		free(cmd);
}

static void	init_cmd(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->pfd[0][0] = -1;
	cmd->pfd[0][1] = -1;
	cmd->pfd[1][0] = -1;
	cmd->pfd[1][1] = -1;
	cmd->type = CT_CMD;
}

int check_cmd_bucket(t_list *cmd)
{
	int stack;
	int cur;

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

int	check_cmd_syntax(t_list *cmd)
{
	int cur;
	int next;

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
		else if (cur == CT_SEMI && (next == CT_SEMI || next == CT_PIPE || next == CT_AND || next == CT_OR))
			return (0);
		else if ((cur == CT_AND || cur == CT_OR || cur == CT_BEGIN) && (next != CT_CMD && next != CT_BEGIN))
			return (0);
		else if (cur == CT_END && (next == CT_CMD || next == CT_PIPE || next == CT_BEGIN))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

t_list	*to_cmd(t_list *token)
{
	t_list	*list;
	t_cmd	*temp;

	list = NULL;
	while (token)
	{
		temp = malloc(sizeof(t_cmd));
		init_cmd(temp);
		if (is_type_token(token->content))
			parse_type_token(&token, temp);
		else
		{
			if (!(temp->argv = parse_argv(&token, temp)))
			{
				free_cmd(temp);
				ft_lstclear(&list, free_cmd);
				ft_lstclear(&token, free);
				return (NULL);
			}
			temp->argv = wildcard(temp->argv);
		}
		ft_lstadd_back(&list, ft_lstnew(temp));
	}
	if (!check_cmd_syntax(list))
	{
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		errno = 258;
		ft_lstclear(&list, free_cmd);
		ft_lstclear(&token, free);
		return (NULL);
	}
	return (list);
}
