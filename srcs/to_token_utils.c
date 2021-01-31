/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:52:37 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/01 04:07:45 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_key_length(char *key)
{
	int i;

	i = 0;
	while (ft_isalnum(key[i]) || key[i] == '_')
		i++;
	return (i);
}

char *find_value(char *str, int n)
{
	char *key;
	t_env *env;

	key = malloc(n + 1);
	key[n] = 0;
	ft_memcpy(key, str, n);
	env = search_env(g_env, key);
	if (!env)
		return (NULL);
	free(key);
	return (env->value);
}

char *token_remove_quote(char *token)
{
	char *it;
	char *ret;
	char *save;

	ret = ft_strdup("");
	it = token;
	save = token;
	while (*it)
	{
		if ((*it == '\'' || *it == '\"') && (it == token || *(it - 1) != '\\'))
		{
			*it = 0;
			ret = ft_strjoin_free_s1(ret, save);
			it++;
			save = it;
		}
		else
			it++;
	}
	ret = ft_strjoin_free_s1(ret, save);
	free(token);
	return (ret);
}

char	*token_switch(char *token)
{
	char *it;
	int flag;
	char *save;
	char *ret;
	int keysize;

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
		{
			*it = 0;
			ret = ft_strjoin_free_s1(ret, save);
			it++;
			keysize = get_key_length(it);
			save = find_value(it, keysize);
			ret = save ? ft_strjoin_free_s1(ret, save) : ret;
			it += keysize;
			save = it;
		}
		else
			it++;
	}
	ret = ft_strjoin_free_s1(ret, save);
	return (ret);
}
