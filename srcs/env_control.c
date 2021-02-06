/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:28:10 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 14:46:12 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(void *value)
{
	t_env	*env;
	int		i;

	i = -1;
	env = value;
	if (!env)
		return ;
	if (!env->key)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

void	*ft_env_dup(void *ref)
{
	t_env	*ret;
	t_env	*env;

	env = ref;
	ret = (t_env *)malloc(sizeof(t_env));
	ret->key = ft_strdup(env->key);
	ret->value = ft_strdup(env->value);
	return (ret);
}

int		ft_env_cmp(void *r1, void *r2)
{
	t_env	*e1;
	t_env	*e2;

	e1 = r1;
	e2 = r2;
	return (ft_strcmp(e1->key, e2->key));
}

t_env	*new_env(char *key, char *value)
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	env->key = key;
	env->value = value;
	return (env);
}
