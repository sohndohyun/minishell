/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:28:09 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/31 14:43:58 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo)
{
	int		status;

	if (signo == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putstr_fd("\n", 1);
		errno = 130;
		print_prompt();
	}
	else if (signo == SIGQUIT)
	{
		signo = wait(&status);
		ft_putstr_fd("\b\b  \b\b", 1);
		errno = 131;
	}
	return ;
}
