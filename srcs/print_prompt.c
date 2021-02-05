/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:24:14 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/05 11:23:46 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	write(STDOUT_FILENO, "minishell$ ", 11);
}
