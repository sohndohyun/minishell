/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:21:12 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/31 16:46:10 by hyeonski         ###   ########.fr       */
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
