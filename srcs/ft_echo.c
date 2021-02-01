/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:12:36 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/01 20:06:28 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **argv)
{
	int		i;
	int		op_n;

	if (argv== NULL || argv[1] == NULL)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		return ;
	}
	op_n = 1;
	while (ft_strcmp(argv[op_n], "-n") == 0)
		op_n++;
	i = op_n - 1;
	while (argv[++i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (op_n == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	errno = 0;
}
