/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:36:24 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/25 20:40:56 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_argv(t_list **token)
{
	char	**argv;
	int		i;

	if (*token == NULL)	
		return (0);
	i = 0;
	argv = malloc(sizeof(char *) * 4);
	while (*token && i < 3
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

int		parse_type(t_list **token)
{
	char	*temp;
	int		type;

	type = 0;
	if (*token == NULL)	
		return (0);
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

	list = NULL;
	while (token)
	{
		temp = malloc(sizeof(t_cmd));
		temp->argv = parse_argv(&token);
		temp->type = parse_type(&token);
		temp->pfd[0][0] = -1;
		temp->pfd[0][1] = -1;
		temp->pfd[1][0] = -1;
		temp->pfd[1][1] = -1;
		ft_lstadd_back(&list, ft_lstnew(temp));
	}
	return (list);
}