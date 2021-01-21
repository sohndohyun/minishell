/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:53:04 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/22 03:27:58 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
			|| c == '\'' || c == '\"' || c == '|');
}

static int		find_token_non_end(char *str)
{
	char *temp;

	temp = str + 1;
	while (*temp)
	{
		if (need_seperate(*temp) && *(temp - 1) != '\\')
			break ;
		temp++;
	}
	return (temp - str);
}

static int		find_token_length(char *str)
{
	int		imsi;

	if (strncmp(*str, "<<", 2) == 0)
		return (2);
	else if (*str == '<' || *str == '|' || *str == '>')
		return (1);
	else if (*str == '\'' || *str == '\"')
	{
		imsi = find_next_ch(str, *str);
		return (imsi != -1 ? imsi + 1 : -1);
	}
	return (find_token_non_end(str));
}

t_list*			to_token(char *str)
{
	t_list *list;

	list = NULL;
	
}
