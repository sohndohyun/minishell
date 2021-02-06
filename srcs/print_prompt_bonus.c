/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:24:14 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 00:56:25 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "termcap_bonus.h"

void	print_prompt(void)
{
	write(STDOUT_FILENO, "minishell$ ", 11);
	g_tc->plen = 11;
}
