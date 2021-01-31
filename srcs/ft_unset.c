/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:21:12 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/31 12:36:08 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_unset_error(char *equation)
{
	char	*temp;
	char	*err_msg;

	errno = 1;
	if ((temp = ft_strjoin("unset: `", equation)) == NULL)
		return ;
	err_msg = ft_strjoin_free_s1(temp, "\'");
	if (err_msg == NULL)
		return ;
	print_error(err_msg, -1, "not a valid identifier");
	free(err_msg);
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *))
{
	t_list *freedom;

	if (*begin_list)
	{
		if ((*cmp)((*begin_list)->content, data_ref) == 0)
		{
			freedom = (*begin_list);
			(*begin_list) = (*begin_list)->next;
			free_fct(freedom->content);
			free(freedom);
			ft_list_remove_if(begin_list, data_ref, cmp, free_fct);
		}
		else
			ft_list_remove_if(&(*begin_list)->next, data_ref, cmp, free_fct);
	}
}

void		ft_unset(char **argv)
{
	t_env	temp;
	
	if (argv == NULL)
		return ;
	argv++;
	while (*argv)
	{
		temp.key = *argv;
		temp.value = NULL;
		if (!is_valid_env_key(*argv))
			print_unset_error(*argv);
		else
			ft_list_remove_if(&g_env, &temp, ft_env_cmp, free_env);
		argv++;
	}
}
