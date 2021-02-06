/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:13 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 00:49:09 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int		ascii_art(void)
{
	int		fd;
	char	*line;

	line = 0;
	if (!(fd = open("ascii_art.txt", O_RDONLY)))
	{
		write(1, "\nError in open\n", 15);
		return (0);
	}
	while (get_next_line(fd, &line) != 0)
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		free(line);
	}
	write(1, line, ft_strlen(line));
	write(1, "\n", 1);
	free(line);
	return (1);
}

int			setup(void)
{
	if (!ascii_art())
		return (0);
	signal(SIGINT, (void *)handle_signal_main);
	signal(SIGQUIT, (void *)handle_signal_main);
	return (1);
}

t_list		*get_env(char **envp)
{
	int		pos;
	t_env	*env;
	t_list	*envs;

	envs = 0;
	while (*envp)
	{
		env = (t_env *)malloc(sizeof(t_env));
		pos = ft_strchr(*envp, '=') - *envp;
		env->key = ft_substr(*envp, 0, pos);
		env->value = ft_substr(*envp, pos + 1, ft_strlen(*envp) - pos - 1);
		ft_lstadd_back(&envs, ft_lstnew(env));
		envp++;
	}
	if (search_env(envs, "OLDPWD") == NULL)
	{
		env = (t_env *)malloc(sizeof(t_env));
		env->key = ft_strdup("OLDPWD");
		env->value = NULL;
		ft_lstadd_back(&envs, ft_lstnew(env));
	}
	return (envs);
}
