/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:06:18 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/04 16:37:31 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <glob.h>

int iswildcard(char *str)
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

int	ft_getargc(char **argv)
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

char **wildcard(char **argv)
{
	int i;
	char **temp;
	glob_t globbuf;
	int argc;
	int imsi;

	i = 0;
	argc = ft_getargc(argv);
	while (argv && argv[i])
	{
		if (iswildcard(argv[i]))
		{
			glob(argv[i], 0, NULL, &globbuf);
			if (globbuf.gl_pathc > 0)
			{
				imsi = argc + globbuf.gl_pathc - 1;
				temp = malloc(sizeof(char*) * (imsi + 1));
				temp[imsi] = 0;
				copy_argv(temp, argv, i);
				copy_argv(temp + i, globbuf.gl_pathv, globbuf.gl_pathc);
				copy_argv(temp + i + globbuf.gl_pathc, argv + i + 1, argc - i - 1);
				ft_free_2d_arr((void**)argv);
				argv = temp;
				i += globbuf.gl_pathc - 1;
				argc = imsi;
			}
			globfree(&globbuf);
		}
		i++;
	}
	return (argv);
}

char *rd_wildcard(char *str)
{
	glob_t globbuf;
	char *temp;

	temp = NULL;
	if (iswildcard(str))
	{
		glob(str, 0, NULL, &globbuf);
		if (globbuf.gl_pathc == 1)
			temp = ft_strdup(globbuf.gl_pathv[0]);
		globfree(&globbuf);
		return (temp);
	}
	else
		return (ft_strdup(str));
}
