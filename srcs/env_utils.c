/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:55:10 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/01 03:07:43 by dsohn            ###   ########.fr       */
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

t_env	*new_env(char *key, char *value)
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	env->key = key;
	env->value = value;
	return (env);
}

void	add_env(t_list *env, char *key, char *value)
{
	ft_lstadd_back(&env, ft_lstnew(new_env(key, value)));
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

t_list	*ft_list_dup(t_list *lst, void *(*dup)(void *))
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	while (lst)
	{
		new = ft_lstnew(dup(lst->content));
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}

int		ft_env_cmp(void *r1, void *r2)
{
	t_env	*e1;
	t_env	*e2;

	e1 = r1;
	e2 = r2;
	return (ft_strcmp(e1->key, e2->key));
}

t_list	*ft_list_sort(t_list *lst, int (*cmp)(void *, void *))
{
	t_list	*begin;
	t_list	*p;
	void	*temp;

	begin = lst;
	while (lst)
	{
		p = lst->next;
		while (p)
		{
			if ((*cmp)(lst->content, p->content) > 0)
			{
				temp = lst->content;
				lst->content = p->content;
				p->content = temp;
			}
			p = p->next;
		}
		lst = lst->next;
	}
	return (begin);
}