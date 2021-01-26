/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 01:49:29 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/26 22:47:26 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_cmd_builtin(char *cmd, int cmd_len)
{
	if(ft_strncmp(cmd, "cd", cmd_len) == 0 || ft_strncmp(cmd, "echo", cmd_len) == 0
	 || ft_strncmp(cmd, "pwd", cmd_len) == 0 || ft_strncmp(cmd, "env", cmd_len) == 0
	 || ft_strncmp(cmd, "export", cmd_len) == 0 || ft_strncmp(cmd, "unset", cmd_len) == 0
	 || ft_strncmp(cmd, "exit", cmd_len) == 0)
		return (1);
	return (0);
}

int run_cmd_builtin(t_cmd *cmd)
{
	int ret;
	int stdout_save;
	int cmd_len;

	cmd_len = ft_strlen(cmd->argv[0]);
	ret = is_cmd_builtin(cmd->argv[0], cmd_len);
	if (cmd->pfd[1][0] != -1 && ret)
	{
		stdout_save = dup(STDOUT_FILENO);
		dup2(cmd->pfd[1][1], 1);
		ret = 1;
	}
	if(ft_strncmp(cmd->argv[0], "cd", cmd_len) == 0)
		ft_cd(cmd->argv);
	else if(ft_strncmp(cmd->argv[0], "echo", cmd_len) == 0)
		ft_echo(cmd->argv);
	else if(ft_strncmp(cmd->argv[0], "pwd", cmd_len) == 0)
		ft_pwd();
	else if(ft_strncmp(cmd->argv[0], "env", cmd_len) == 0)
		ft_env(g_env);
	else if(ft_strncmp(cmd->argv[0], "export", cmd_len) == 0)
		printf("TODO: %s\n", cmd->argv[0]);
	else if(ft_strncmp(cmd->argv[0], "unset", cmd_len) == 0)
		printf("TODO: %s\n", cmd->argv[0]);
	else if(ft_strncmp(cmd->argv[0], "exit", cmd_len) == 0)
		printf("TODO: %s\n", cmd->argv[0]);
	if (cmd->pfd[1][0] != -1 && ret)
	{
		close(cmd->pfd[1][1]);
		dup2(stdout_save, STDOUT_FILENO);
	}
	return (ret);
}

void run_cmd(t_cmd *cmd)
{
	if (!run_cmd_builtin(cmd))
	{
		execvp(cmd->argv[0], cmd->argv);
		printf("execvp_error!");
		exit(1);
	}
	exit(0);
}
