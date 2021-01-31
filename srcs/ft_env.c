/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:59:43 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/31 16:45:39 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	if (env->value != NULL)
	{
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putendl_fd(env->value, STDOUT_FILENO);
	}
}

void	ft_env(t_list *env)
{
	while (env)
	{
		if (env->content)
			print_env(env->content);
		env = env->next;
	}
	errno = 0;
}