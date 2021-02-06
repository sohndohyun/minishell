/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:27:06 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 14:49:54 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_and_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	ft_free_2d_arr(void **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

char	*ft_strjoin_free_s1(char const *s1, char const *s2)
{
	int			idx;
	int			idx_join;
	char		*join;

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

int		get_word_count(char *str, char *set)
{
	int		i;
	int		cnt;
	
	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (ft_strchr(set, str[i]) != NULL)
		{
			cnt++;
			i++;
		}
		else
		{
			cnt++;
			if (str[i] == '$')
				i++;
			while (str[i] && str[i] != '$' && ft_strchr(set, str[i]) == NULL)
				i++;
		}
	}
	return (cnt);
}

int		ft_nbr_length(int n)
{
	int i;

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

void free_strarr(char **arr)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
