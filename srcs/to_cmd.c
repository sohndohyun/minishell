/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:36:24 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/26 19:39:52 by hyeonski         ###   ########.fr       */
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
		i++;
		token = token->next;
	}
	return (i);
}

char	**parse_argv(t_list **token)
{
	char	**argv;
	int		i;
	int		len;

	if (*token == NULL)	
		return (0);
	i = 0;
	len = get_argv_len(*token);
	argv = malloc(sizeof(char *) * (len + 1));
	while (*token
	&& ft_strcmp((*token)->content, "|") != 0
	&& ft_strcmp((*token)->content, ";") != 0)
	{
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
		temp->type = parse_type(&token, flag);
		temp->argv = parse_argv(&token);
		temp->pfd[0][0] = -1;
		temp->pfd[0][1] = -1;
		temp->pfd[1][0] = -1;
		temp->pfd[1][1] = -1;
		ft_lstadd_back(&list, ft_lstnew(temp));
		flag = 0;
	}
	return (list);
}