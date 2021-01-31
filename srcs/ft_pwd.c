/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:58:52 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/31 15:00:36 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	dir[4096];

	if (getcwd(dir, 4096) == NULL)
		print_error("pwd", errno, strerror(errno));
	else
		ft_putendl_fd(dir, STDOUT_FILENO);
}
