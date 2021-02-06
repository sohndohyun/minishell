/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:45:21 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 00:49:52 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_first_equal_char(int *pos, char *str)
{
	*pos = 0;
	while (str[*pos] != '=' && str[*pos] != '\0')
		(*pos)++;
	if (*pos == 0)
		return (0);
	return (1);
}

int			is_valid_env_key(char *key)
{
	int		is_first;

	if (!key)
		return (0);
	is_first = 1;
	while (*key)
	{
		if (is_first == 1 && ft_isdigit(*key))
			return (0);
		if (!ft_isalnum(*key) && *key != '_')
		{
			if (*key == '+' && *(key + 1) == '\0')
				return (1);
			return (0);
		}
		key++;
		is_first = 0;
	}
	return (1);
}
