/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:28:09 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/25 10:01:26 by hyeonski         ###   ########.fr       */
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
		print_prompt();
	}
	else if (signo == SIGQUIT)
	{
		signo = wait(&status);
		ft_putstr_fd("\b\b  \b\b", 1);
	}
	return ;
}
