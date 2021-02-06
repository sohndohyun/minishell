/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_util_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:28:21 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/06 23:54:22 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

int		iswildcard(char *str)
{
	int i;

	if (str && str[0] == '-')
		return (0);
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '*' && (i == 0 || str[i - 1] != '\\'))
			return (1);
		i++;
	}
	return (0);
}

int		ft_getargc(char **argv)
{
	int i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

void	copy_argv(char **dst, char **src, int n)
{
	int i;

	i = 0;
	if (!dst || !src)
		return ;
	while (src[i] && i < n)
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
}
