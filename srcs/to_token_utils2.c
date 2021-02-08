/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:45:34 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/09 03:56:39 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
