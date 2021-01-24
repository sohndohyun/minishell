/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 01:49:29 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/25 03:55:52 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int run_cmd_builtin(t_cmd *cmd)
{
	if(ft_strncmp(cmd->argv[0], "cd", ft_strlen(cmd->argv[0])) == 0)
		printf("TODO: %s\n", cmd->argv[0]);
	else if(ft_strncmp(cmd->argv[0], "echo", ft_strlen(cmd->argv[0])) == 0)
		printf("TODO: %s\n", cmd->argv[0]);
	else if(ft_strncmp(cmd->argv[0], "pwd", ft_strlen(cmd->argv[0])) == 0)
		printf("TODO: %s\n", cmd->argv[0]);
	else if(ft_strncmp(cmd->argv[0], "env", ft_strlen(cmd->argv[0])) == 0)
		printf("TODO: %s\n", cmd->argv[0]);
	else if(ft_strncmp(cmd->argv[0], "export", ft_strlen(cmd->argv[0])) == 0)
		printf("TODO: %s\n", cmd->argv[0]);
	else if(ft_strncmp(cmd->argv[0], "unset", ft_strlen(cmd->argv[0])) == 0)
		printf("TODO: %s\n", cmd->argv[0]);
	else if(ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0])) == 0)
		printf("TODO: %s\n", cmd->argv[0]);
	else
		return (0);
	return (1);
}

void run_cmd(t_cmd *cmd)
{
	if (!run_cmd_builtin(cmd))
	{
		execvp(cmd->argv[0], cmd->argv);
		printf("execvp_error!");
	}
	exit(1);
}
