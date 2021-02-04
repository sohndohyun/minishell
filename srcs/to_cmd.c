/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:36:24 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/04 16:39:09 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_type_token(char *str)
{
	return (ft_strcmp(str, "|") == 0 || ft_strcmp(str, ";") == 0
	|| ft_strcmp(str, "&&") == 0 || ft_strcmp(str, "||") == 0);
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

int		parse_type(t_list **token, int flag)
{
	char	*temp;
	int		type;

	type = 0;
	if (*token == NULL)	
		return (0);
	if (flag == 1)
		return (CT_NORM);	
	if (is_type_token((*token)->content))
	{
		temp = (*token)->content;
		if (ft_strcmp(temp, "||") == 0)
			type = CT_OR;
		else if (ft_strcmp(temp, "&&") == 0)
			type = CT_AND;
		else if (ft_strcmp(temp, "|") == 0)
			type = CT_PIPE;
		else
			type = CT_NORM;
	}
	if (!(*token)->next && type == CT_NORM)
		return (0);
	if ((*token)->next && is_type_token((*token)->next->content))
	{
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		return (-1);
	}
	(*token) = (*token)->next;
	return (type);
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
	cmd->type = ';';
}

t_list	*to_cmd(t_list *token)
{
	t_list	*list;
	t_cmd	*temp;
	int		flag;

	flag = 1;
	list = NULL;
	while (token)
	{
		temp = malloc(sizeof(t_cmd));
		init_cmd(temp);
		temp->type = parse_type(&token, flag);
		if (temp->type == 0)
		{
			free_cmd(temp);
			return (list);
		}
		else if (temp->type == -1)
		{
			free_cmd(temp);
			ft_lstclear(&list, free_cmd);
			return (NULL);
		}
		temp->argv = parse_argv(&token, temp);
		if (temp->argv == NULL)
		{
			free_cmd(temp);
			ft_lstclear(&list, free_cmd);
			return (NULL);
		}
		temp->argv = wildcard(temp->argv);
		ft_lstadd_back(&list, ft_lstnew(temp));
		flag = 0;
	}
	return (list);
}
