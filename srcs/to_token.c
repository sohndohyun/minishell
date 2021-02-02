/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:53:04 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/02 12:34:36 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		find_next_ch(char *str, char c)
{
	char *temp;

	temp = str + 1;
	while (*temp)
	{
		if (*temp == c && *(temp - 1) != '\\')
			return (temp - str);
		temp++;
	}
	return (-1);
}

static int		need_seperate(char c)
{
	return (ft_isspace(c) || c == '<' || c == '>'
			|| c == '|' || c == ';');
}

static int		find_token_non_end(char *str)
{
	char *temp;
	int imsi;

	if (*str == '\'' || *str == '\"')
	{
		imsi = find_next_ch(str, *str);
		if (imsi == -1)
			return (-1);
		temp = str + imsi + 1;
	}
	else 
		temp = str + 1;
	while (*temp)
	{
		if (need_seperate(*temp) && *(temp - 1) != '\\')
			break ;
		else if ((*temp == '\'' || *temp == '\"') && *(temp - 1) != '\\')
		{
			imsi = find_next_ch(temp, *temp);
			if (imsi == -1)
				return (-1);
			temp += imsi;
		}
		temp++;
	}
	return (temp - str);
}

static int		find_token_length(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
		return (2);
	else if (*str == '<' || *str == '|' || *str == '>')
		return (1);
	return (find_token_non_end(str));
}

t_list			*to_token(char *str)
{
	t_list	*list;
	int		token_len;
	char	*temp;
	int i;

	list = NULL;
	str = token_switch(str);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else
		{
			token_len = find_token_length(str + i);
			if (token_len == -1)
			{
				ft_lstclear(&list, free);
				ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
				free(str);
				return (NULL);
			}
			temp = malloc(token_len + 1);
			temp[token_len] = '\0';
			ft_strlcpy(temp, str + i, token_len + 1);
			temp = token_remove_quote(temp);
			ft_lstadd_back(&list, ft_lstnew(temp));
			i += token_len;
		}
	}
	free(str);
	return (list);
}
