/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bigtoken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 03:38:54 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/09 02:54:48 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		need_seperate(char *c)
{
	return (ft_strncmp(c, "&&", 2) == 0 || ft_strncmp(c, "||", 2) == 0
		|| ft_strncmp(c, ";", 1) == 0 || ft_strncmp(c, "(", 1) == 0
		|| ft_strncmp(c, ")", 1) == 0);
}

static int		find_token_non_end(char *str)
{
	char		*temp;
	int			imsi;

	if (*str == '\'' || *str == '\"')
	{
		imsi = find_next_ch(str, str, *str);
		if (imsi == -1)
			return (-1);
		temp = str + imsi + 1;
	}
	else
		temp = str + 1;
	while (*temp)
	{
		if (need_seperate(temp))
			break ;
		else if (*temp == '\'' || *temp == '\"')
		{
			if ((imsi = find_next_ch(temp, str, *temp)) == -1)
				return (-1);
			temp += imsi;
		}
		temp++;
	}
	return (temp - str);
}

static int		find_token_length(char *str)
{
	if (ft_strncmp(str, "||", 2) == 0 || ft_strncmp(str, "&&", 2) == 0)
		return (2);
	else if (*str == '(' || *str == ')' || *str == ';')
		return (1);
	return (find_token_non_end(str));
}

t_list			*to_bigtoken(char *str)
{
	t_list		*list;
	int			token_len;
	char		*temp;
	int			i;

	list = NULL;
	i = 0;
	str = ft_strdup(str);
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else
		{
			token_len = find_token_length(str + i);
			if (token_len == -1)
				return (handle_syntax_error(&list, str));
			temp = ft_substr(str + i, 0, token_len);
			ft_lstadd_back(&list, ft_lstnew(temp));
			i += token_len;
		}
	}
	free(str);
	return (list);
}
