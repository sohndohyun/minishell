/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:45:34 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/09 04:39:52 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

int		is_before_backslash(char *str, char *begin)
{
	int cnt;

	cnt = 0;
	if (str == begin)
		return (0);
	str--;
	while (str >= begin && *str == '\\')
	{
		cnt++;
		str--;
	}
	return (cnt % 2 == 0 ? 0 : 1);
}

int		find_next_ch(char *str, char *begin, char c)
{
	char *temp;

	temp = str + 1;
	while (*temp)
	{
		if (*temp == c && !(c == '\"' && is_before_backslash(temp, begin)))
			return (temp - str);
		temp++;
	}
	return (-1);
}

char	*token_remove_backslash(char *token)
{
	char *it;
	char *ret;
	char *save;

	ret = ft_strdup("");
	save = token;
	it = token;
	while (*it)
		if (*it == '\\' && (it[1] == '\\' || it[1] == '$' || it[1] == '\"'))
		{
			*it = 0;
			ret = ft_strjoin_free_s1(ret, save);
			save = ft_strdup(" ");
			save[0] = it[1];
			ret = ft_strjoin_free_s1(ret, save);
			free(save);
			it += 2;
			save = it;
		}
		else
			it++;
	ret = ft_strjoin_free_s1(ret, save);
	free(token);
	return (ret);
}

char	*token_remove_quote(char *token)
{
	char	c;
	int		len;

	c = token[0];
	if (c == '\'' || c == '\"')
	{
		len = ft_strlen(token);
		ft_memmove(token, token + 1, len);
		token[len - 2] = 0;
	}
	if (c == '\"')
		token = token_remove_backslash(token);
	return (token);
}
