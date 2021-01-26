/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_switch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:35:40 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/26 20:22:53 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_keyascii(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char *lst_same_str(t_list *env, char *str, int n)
{
	t_env *nv;

	while (env)
	{
		nv = env->content;
		if (ft_strncmp(nv->key, str, n) == 0)
			return (nv->value);
		env = env->next;		
	}
	return ("");
}

static void	str_switch_env(char *str, t_list *env)
{
	int i, save, j;
	char *rst;

	i = 0;
	save = 0;
	rst = NULL;
	while (str[i])
	{
		if (str[i] == '$' && (i == 0 || str[i - 1] != '\\'))
		{
			if (is_keyascii(str[i + 1]) || str[i + 1] == '?')
			{
				str[i] = 0;
				rst = ft_strjoin_free_s1(rst, str + save);
				i++;
			}
			if (is_keyascii(str[i]))
			{
				j = i + 1;
				while (is_keyascii(str[j]))
					j++;
				rst = ft_strjoin_free_s1(rst, lst_same_str(env, str + i, j));
				i += j;
				save = i;
			}
			else if (str[i] == '?')
			{
				rst = ft_strjoin_free_s1(rst, lst_same_str(env, "?", 1));
				save = ++i;
			}
		}
		else
			i++;
	}
	if (rst)
	{
		free(str);
		str = rst;
	}
}

void	token_switch(t_list *token, t_list *env)
{
	t_list *it;
	char *str;

	it = token;
	while (it)
	{
		str = it->content;
		if(str && str[0] != '\'')
			str_switch_env(it->content, env);
		it = it->next;
	}
}
