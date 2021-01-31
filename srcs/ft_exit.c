/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 12:35:01 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/31 14:30:02 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			print_exit_error(char *arg)
{
	char			*temp;

	if ((temp = ft_strjoin("exit: ", arg)) == NULL)
		return (1);
	print_error(temp, -1, "numeric argument required");
	free(temp);
	return (255);
}

int					ft_exit(char **argv)
{
	char			*test;
	int				temp;
	unsigned char	result;

	ft_putendl_fd("exit", STDOUT_FILENO);
	argv++;
	test = *argv;
	while (*test)
	{
		if (!ft_isdigit(*test))
			return (print_exit_error(*argv));
		test++;
	}
	if (argv[1] != NULL)
	{
		errno = 1;
		print_error("exit", -1, "too many arguments");
		return (1);
	}
	temp = ft_atoi(*argv);
	result = (unsigned char)temp;
	return (result);
}
