/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:28:09 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 23:26:36 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal_main(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("  \b\b", 1);
		ft_putstr_fd("\n", STDERR_FILENO);
		reinit_termcap();
		print_prompt();
		signal(SIGINT, handle_signal_main);
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
	}
}

void	handle_signal_chlid(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		signal(SIGINT, handle_signal_main);
	}
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		signal(SIGQUIT, handle_signal_main);
	}
}
