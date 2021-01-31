/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 01:49:29 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/31 16:42:59 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int is_cmd_builtin(char *cmd)
{
	int cmd_len;

	cmd_len = ft_strlen(cmd);
	if(ft_strncmp(cmd, "cd", cmd_len) == 0 || ft_strncmp(cmd, "echo", cmd_len) == 0
	 || ft_strncmp(cmd, "pwd", cmd_len) == 0 || ft_strncmp(cmd, "env", cmd_len) == 0
	 || ft_strncmp(cmd, "export", cmd_len) == 0 || ft_strncmp(cmd, "unset", cmd_len) == 0
	 || ft_strncmp(cmd, "exit", cmd_len) == 0)
		return (1);
	return (0);
}

int run_cmd_builtin_run(t_cmd *cmd)
{
	int cmd_len;
	int	status;

	cmd_len = ft_strlen(cmd->argv[0]);
	if(ft_strcmp(cmd->argv[0], "cd") == 0)
		ft_cd(cmd->argv);
	else if(ft_strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(cmd->argv);
	else if(ft_strcmp(cmd->argv[0], "pwd") == 0)
		ft_pwd();
	else if(ft_strcmp(cmd->argv[0], "env") == 0)
		ft_env(g_env);
	else if(ft_strcmp(cmd->argv[0], "export") == 0)
		ft_export(cmd->argv);
	else if(ft_strcmp(cmd->argv[0], "unset") == 0)
		ft_unset(cmd->argv);
	else if(ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		if ((status = ft_exit(cmd->argv)) != 1)
			exit(status);
	}
	return (0);
}

int run_cmd_builtin(t_cmd *cmd)
{
	if (cmd->pfd[1][0] != -1 || cmd->pfd[0][0] != -1)
		return run_cmd(cmd, run_cmd_builtin_run);
	else 
		return run_cmd_builtin_run(cmd);
}

void free_strarr(char **arr)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char *find_path(char *cmd, t_list *env)
{
	char *path;
	char **paths;
	char *temp;
	int i;
	struct stat s;
	
	if (!(temp = search_env(env, "PATH")->value))
		return (NULL);
	paths = ft_split(temp, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin("/", cmd);
		path = ft_strjoin(paths[i], temp);
		free(temp);
		if (stat(path, &s) == 0)
		{
			free_strarr(paths);
			return (path);
		}
		free(path);
	}
	free_strarr(paths);
	return (ft_strdup(cmd));
}

char **get_envp(t_list *env_list)
{
	int temp1;
	int temp2;
	char **ret;
	int i;
	t_env *env;

	i = 0;
	temp1 = ft_lstsize(env_list);
	ret = malloc(sizeof(char*) * (temp1 + 1));
	ret[temp1] = 0;
	while (env_list)
	{
		env = env_list->content;
		temp1 = ft_strlen(env->key);
		temp2 = ft_strlen(env->value);
		ret[i] = malloc(temp1 + temp2 + 2);
		ft_memcpy(ret[i], env->key, temp1);
		ret[i][temp1] = '=';
		ft_memcpy(ret[i] + temp1 + 1, env->value, temp2);
		ret[i][temp1 + temp2 + 1] = 0;
		env_list = env_list->next;
		i++;
	}
	return (ret);
}

int run_cmd_execve(t_cmd *cmd)
{
	char *path;
	char **envp;

	path = find_path(cmd->argv[0], g_env);
	if (!path)
	{
		ft_putendl_fd("minishell: command not found", STDERR_FILENO);
		return (1);
	}
	envp = get_envp(g_env);
	execve(path, cmd->argv, envp);
	ft_putendl_fd("minishell: command not found", STDERR_FILENO);
	return (1);
}

int run_cmd(t_cmd *cmd, int (*run_cmd_type)(t_cmd*))
{
	int status;
	pid_t	pid;

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
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
