/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:52:37 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/09 04:42:16 by dsohn            ###   ########.fr       */
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

void		switch_value(char **ret, char **it, char **save)
{
	int		keysize;

	**it = '\0';
	*ret = ft_strjoin_free_s1(*ret, *save);
	(*it)++;
	keysize = get_key_length(*it);
	*save = keysize > 0 ? find_value(*it, keysize) : ft_strdup("$");
	*ret = *save ? ft_strjoin_free_s1(*ret, *save) : *ret;
	free(*save);
	*it += keysize;
	*save = *it;
}

static int	checkflag(int flag, char *it, char *token)
{
	return (!(flag == '\"' && is_before_backslash(it, token)));
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
		if ((*it == '\'' || *it == '\"'))
		{
			if (flag == 0)
				flag = *it;
			else if (flag == *it && checkflag(flag, it, token))
				flag = 0;
		}
		if (*it == '$' && flag != '\'' && checkflag(flag, it, token))
			switch_value(&ret, &it, &save);
		else
			it++;
	}
	ret = ft_strjoin_free_s1(ret, save);
	return (ret);
}
