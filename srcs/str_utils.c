/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:19:53 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 21:21:00 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_middle(char *s1, const char *s2, int div)
{
	char	*str;
	int		l;

	l = ft_strlen(s1) + 1;
	if (!s2)
	{
		str = ft_strdup(s1);
		free((void*)s1);
		return (str);
	}
	if (!(str = (char*)malloc(sizeof(char) * (l + 2))))
		return (NULL);
	ft_strlcpy(str, s1, div);
	str[div] = '\0';
	ft_strcat(str, s2);
	while (div < l)
	{
		str[div] = s1[div - 1];
		div++;
	}
	ft_free_and_null((void **)&s1);
	str[div] = '\0';
	return (str);
}

char	*ft_strjoin_middle2(char *s1, const char *s2, int div)
{
	char	*str;
	int		l;
	char	*tmp;

	if (!s2)
	{
		str = ft_strdup(s1);
		free((void*)s1);
		return (str);
	}
	l = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char*)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	ft_strlcpy(str, s1, div + 1);
	ft_strcat(str, s2);
	tmp = ft_substr(s1, div, ft_strlen(s1) - div);
	ft_strcat(str, tmp);
	free(tmp);
	return (str);
}

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		i;

	i = ft_strlen(s1);
	while (*s2 && n)
	{
		s1[i] = *s2;
		i++;
		s2++;
		n--;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strcat(char *dst, const char *src)
{
	int		i;
	int		j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_dups1_frees2(const char *s1, char *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	while (s1[i])
	{
		str[i] = (char)s1[i];
		i++;
	}
	str[i] = '\0';
	free(s2);
	s2 = NULL;
	return (str);
}
