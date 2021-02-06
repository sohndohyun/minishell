/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:06:18 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/06 23:55:49 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

void	wildcard_inloop(char **argv, int i, int *argc)
{
	glob_t	globbuf;
	int		imsi;
	char	**temp;

	glob(argv[i], 0, NULL, &globbuf);
	if (globbuf.gl_pathc > 0)
	{
		imsi = *argc + globbuf.gl_pathc - 1;
		temp = malloc(sizeof(char*) * (imsi + 1));
		temp[imsi] = 0;
		copy_argv(temp, argv, i);
		copy_argv(temp + i, globbuf.gl_pathv, globbuf.gl_pathc);
		copy_argv(temp + i + globbuf.gl_pathc,
			argv + i + 1, *argc - i - 1);
		ft_free_2d_arr((void**)argv);
		argv = temp;
		i += globbuf.gl_pathc - 1;
		*argc = imsi;
	}
	globfree(&globbuf);
}

char	**wildcard(char **argv)
{
	int		i;
	int		argc;

	i = 0;
	argc = ft_getargc(argv);
	while (argv && argv[i])
	{
		if (iswildcard(argv[i]))
			wildcard_inloop(argv, i, &argc);
		i++;
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
