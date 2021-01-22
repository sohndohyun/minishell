/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:27:06 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/22 13:54:44 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_and_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	ft_free_2d_arr(void	 **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

char	*ft_strjoin_free_s1(char const *s1, char const *s2)
{
	char	*result;
	int		s1_len;
	int		s2_len;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (0);
	i = -1;
	while (++i < s1_len)
		result[i] = s1[i];
	i--;
	while (i++ < s1_len + s2_len)
		result[i] = s2[i - s1_len];
	result[i] = 0;
	ft_free_and_null((void **)&s1);
	return (result);
}
