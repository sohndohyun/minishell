/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:55:10 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/31 15:02:15 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_equal_key(t_env *env, char *key)
{
	if (ft_strcmp(env->key, key) == 0)
		return (1);
	return (0);
}

t_env	*search_env(t_list *env, char *key)
{
	while (env)
	{
		if (env->content)
			if (is_equal_key(env->content, key))
				return (env->content);
		env = env->next;
	}
	return (NULL);
}

void	modify_value(t_env *env, char *value)
{
	free(env->value);
	env->value = value;
}

void	modify_env(t_list *env, char *key, char *value)
{
	while (env)
	{
		if (env->content)
			if (is_equal_key(env->content, key))
				modify_value(env->content, value);
		env = env->next;
	}
}
