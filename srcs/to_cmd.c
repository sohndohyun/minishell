/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:36:24 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/31 11:12:53 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_argv_len(t_list *token)
{
	int i;

	i = 0;
	while (token
	&& ft_strcmp(token->content, "|") != 0
	&& ft_strcmp(token->content, ";") != 0)
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
		return (0);
	i = 0;
	len = get_argv_len(*token);
	if (len == -1)
	{
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		return (NULL);
	}
	argv = malloc(sizeof(char *) * (len + 1));
	while (*token
	&& ft_strcmp((*token)->content, "|") != 0
	&& ft_strcmp((*token)->content, ";") != 0)
	{
		if (is_redirection((*token)->content))
		{
			if (!to_cmd_redirection((*token)->content, (*token)->next->content, cmd))
			{
				free(argv);
				ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
				print_error((*token)->next->content, 2, strerror(2));
				return (NULL);
			}
			(*token) = (*token)->next->next;
			continue;
		}
		argv[i] = (*token)->content;
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
		return (';');	
	if (ft_strcmp((*token)->content, "|") == 0
	|| ft_strcmp((*token)->content, ";") == 0)
	{
		temp = (*token)->content;
		type = temp[0];
	}
	(*token) = (*token)->next;
	return (type);
}

void	free_cmd(void *value)
{
	t_cmd *cmd;
	int i;

	i = -1;
	cmd = value;
	if (!cmd)
		return ;
	if (!cmd->argv)
		return ;
	free(cmd->argv);
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
		temp->argv = parse_argv(&token, temp);
		if (temp->argv == NULL)
		{
			free_cmd(temp);
			ft_lstclear(&list, free_cmd);
			return (NULL);
		}
		ft_lstadd_back(&list, ft_lstnew(temp));
		flag = 0;
	}
	return (list);
}
