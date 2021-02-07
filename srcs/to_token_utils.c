/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:52:37 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/08 00:50:16 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "utils.h"

int			get_key_length(char *key)
{
	int		i;

	i = 0;
	if (ft_strcmp(key, "?") == 0)
		return (ft_nbr_length(errno));
	while (ft_isalnum(key[i]) || key[i] == '_')
		i++;
	return (i);
}

char		*find_value(char *str, int n)
{
	char	*key;
	t_env	*env;

	if (ft_strcmp(str, "?") == 0)
		return (ft_itoa(errno));
	key = malloc(n + 1);
	key[n] = 0;
	ft_memcpy(key, str, n);
	env = search_env(g_env, key);
	free(key);
	if (!env)
		return (NULL);
	return (ft_strdup(env->value));
}

char		*token_remove_quote(char *token, char *it, char *save, int flag)
{
	char	*ret;

	ret = ft_strdup("");
	while (*it)
		if (flag == *it && (it == token || *(it - 1) != '\\'))
		{
			flag = 0;
			*it++ = 0;
			ret = ft_strjoin_free_s1(ret, save);
			save = it;
		}
		else if ((*it == '\'' || *it == '\"') &&
			(it == token || *(it - 1) != '\\') && flag == 0)
		{
			flag = *it;
			*it++ = 0;
			ret = ft_strjoin_free_s1(ret, save);
			save = it;
		}
		else
			it++;
	ret = ft_strjoin_free_s1(ret, save);
	free(token);
	return (ret);
}

void		switch_value(char **ret, char **it, char **save)
{
	int		keysize;

	**it = '\0';
	*ret = ft_strjoin_free_s1(*ret, *save);
	(*it)++;
	keysize = get_key_length(*it);
	*save = find_value(*it, keysize);
	*ret = *save ? ft_strjoin_free_s1(*ret, *save) : *ret;
	free(*save);
	*it += keysize;
	*save = *it;
}

char		*token_switch(char *token)
{
	char	*it;
	int		flag;
	char	*save;
	char	*ret;

	it = token;
	flag = 0;
	save = token;
	ret = ft_strdup("");
	while (*it)
	{
		if ((*it == '\'' || *it == '\"') && (it == token || *(it - 1) != '\\'))
		{
			if (flag == 0)
				flag = *it;
			else if (flag == *it)
				flag = 0;
		}
		if (*it == '$' && (it == token || *(it - 1) != '\\') && flag != '\'')
			switch_value(&ret, &it, &save);
		else
			it++;
	}
	ret = ft_strjoin_free_s1(ret, save);
	return (ret);
}
