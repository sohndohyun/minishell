/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:21:12 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/02 00:43:06 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_unset_error(char *id)
{
	char	*temp;
	char	*err_msg;

	errno = 1;
	if ((temp = ft_strjoin("unset: `", id)) == NULL)
		return (errno);
	err_msg = ft_strjoin_free_s1(temp, "\'");
	if (err_msg == NULL)
		return (errno);
	print_error(err_msg, -1, "not a valid identifier");
	free(err_msg);
	return (errno);
}

int		ft_unset(char **argv)
{
	t_env	temp;
	
	if (argv == NULL)
		return (1);
	argv++;
	while (*argv)
	{
		temp.key = *argv;
		temp.value = NULL;
		if (!is_valid_env_key(*argv))
			return (print_unset_error(*argv));
		else
			ft_list_remove_if(&g_env, &temp, ft_env_cmp, free_env);
		argv++;
	}
	return (0);
}
