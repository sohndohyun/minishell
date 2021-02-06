/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:27:06 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 00:52:45 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_free_and_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void		ft_free_2d_arr(void **ptr)
{
	int		i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

char		*ft_strjoin_free_s1(char const *s1, char const *s2)
{
	int		idx;
	int		idx_join;
	char	*join;

	if (!s1 || !s2 || !(join = malloc(sizeof(char) *
					(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1))))
		return (NULL);
	idx = 0;
	idx_join = 0;
	while (s1[idx])
		join[idx_join++] = s1[idx++];
	idx = 0;
	while (s2[idx])
		join[idx_join++] = s2[idx++];
	join[idx_join] = '\0';
	ft_free_and_null((void **)&s1);
	return (join);
}

int			ft_nbr_length(int n)
{
	int		i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void		free_strarr(char **arr)
{
	int		i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
