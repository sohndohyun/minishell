/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:06:18 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/09 02:40:34 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"
#include "utils.h"

char	**wildcard_temp(char **argv, int i, glob_t *globbuf, int argc)
{
	char	**temp;
	int		imsi;

	imsi = argc + globbuf->gl_pathc - 1;
	temp = ft_calloc(sizeof(char*), (imsi + 1));
	copy_argv(temp, argv, i);
	copy_argv(temp + i, globbuf->gl_pathv, globbuf->gl_pathc);
	copy_argv(temp + i + globbuf->gl_pathc,
		argv + i + 1, argc - i - 1);
	return (temp);
}

char	**wildcard(char **argv)
{
	int		i;
	int		argc;
	glob_t	globbuf;
	int		imsi;
	char	**temp;

	i = -1;
	argc = ft_getargc(argv);
	while (argv && argv[++i])
		if (iswildcard(argv[i]))
		{
			glob(argv[i], 0, NULL, &globbuf);
			if (globbuf.gl_pathc > 0)
			{
				imsi = argc + globbuf.gl_pathc - 1;
				temp = wildcard_temp(argv, i, &globbuf, argc);
				ft_free_2d_arr((void**)argv);
				argv = temp;
				i += globbuf.gl_pathc - 1;
				argc = imsi;
			}
			globfree(&globbuf);
		}
	return (argv);
}

char	*rd_wildcard(char *str)
{
	glob_t	globbuf;
	char	*temp;

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
