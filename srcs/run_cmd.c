/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 01:49:29 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/07 00:49:15 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_cmd_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int		run_cmd_builtin_run(t_cmd *cmd)
{
	int cmd_len;
	int	status;

	cmd_len = ft_strlen(cmd->argv[0]);
	status = 0;
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		status = ft_cd(cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		status = ft_echo(cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		status = ft_env(g_env);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		status = ft_export(cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		status = ft_unset(cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		if ((status = ft_exit(cmd->argv)) != 1)
			exit(status);
	}
	return (status);
}

int		run_cmd_builtin(t_cmd *cmd)
{
	if (cmd->pfd[1][0] != -1 || cmd->pfd[0][0] != -1)
		return (run_cmd(cmd, run_cmd_builtin_run));
	else
		return (run_cmd_builtin_run(cmd));
}

int		run_cmd_execve(t_cmd *cmd)
{
	char *path;
	char **envp;

	path = find_path(cmd->argv[0], g_env);
	if (!path)
	{
		ft_putendl_fd("minishell: command not found", STDERR_FILENO);
		return (127);
	}
	envp = get_envp(g_env);
	execve(path, cmd->argv, envp);
	ft_putendl_fd("minishell: command not found", STDERR_FILENO);
	return (127);
}

int		run_cmd(t_cmd *cmd, int (*run_cmd_type)(t_cmd*))
{
	pid_t	pid;

	signal(SIGQUIT, handle_signal_chlid);
	if (!(pid = fork()))
	{
		if (cmd->pfd[0][0] != -1)
			dup2(cmd->pfd[0][0], 0);
		if (cmd->pfd[1][0] != -1)
			dup2(cmd->pfd[1][1], 1);
		exit(run_cmd_type(cmd));
	}
	if (cmd->pfd[0][0] != -1)
		close(cmd->pfd[0][0]);
	if (cmd->pfd[1][0] != -1)
		close(cmd->pfd[1][1]);
	return (wait_child(pid));
}
