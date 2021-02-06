/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:30:47 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/06 22:39:59 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"
#include "minishell.h"

char	*find_path(char *cmd, t_list *env)
{
	char		*path;
	char		**paths;
	char		*temp;
	int			i;
	struct stat	s;

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

void	kvlen(char *s1, char *s2, int *key, int *value)
{
	*key = ft_strlen(s1);
	*value = ft_strlen(s2);
}

char	**get_envp(t_list *env_list)
{
	int		temp1;
	int		temp2;
	char	**ret;
	int		i;
	t_env	*env;

	i = 0;
	ret = malloc(sizeof(char*) * (ft_lstsize(env_list) + 1));
	while (env_list)
	{
		env = env_list->content;
		if (env->value)
		{
			kvlen(env->key, env->value, &temp1, &temp2);
			ret[i] = malloc(temp1 + temp2 + 2);
			ft_memcpy(ret[i], env->key, temp1);
			ret[i][temp1] = '=';
			ft_memcpy(ret[i] + temp1 + 1, env->value, temp2);
			ret[i][temp1 + temp2 + 1] = 0;
			i++;
		}
		env_list = env_list->next;
	}
	ret[i] = NULL;
	return (ret);
}

int		wait_child(pid_t pid)
{
	int		signo;
	int		status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		if (signo == SIGINT)
			return (130);
		if (signo == SIGQUIT)
			return (131);
	}
	return (WEXITSTATUS(status));
}
