/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:27:06 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/29 14:55:06 by hyeonski         ###   ########.fr       */
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

char	**ft_split_token(char *str, char *set)
{
	char	**result;
	int		word_cnt;
	int		i;
	int		j;
	int		word_idx;
	

	word_cnt = get_word_count(str, set);
	if ((result = (char **)malloc(sizeof(char *) * (word_cnt + 1))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	word_idx = 0;
	while (str[i] && str[j] && word_idx < word_cnt)
	{
		if (str[j])
			j++;
		while (str[j] && str[j] != '$' && ft_strchr(set, str[j]) == NULL)
			j++;
		result[word_idx++] = ft_substr(str + i, 0, j - i);
		i = j;
	}
	if (str[i] != '\0')
		result[word_idx++] = ft_substr(str + i, 0, j - i);
	result[word_idx] = NULL;
	return (result);
}
