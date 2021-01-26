/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:44:15 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/26 22:00:35 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_env;

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

int		setup(void)
{
	if (!ascii_art())
		return (0);
	signal(SIGINT, (void *)handle_signal);
	signal(SIGQUIT, (void *)handle_signal);
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
	return (envs);
}

void	print_cmd(t_cmd *cmd)
{
	int i;
	char **temp;

	i = 0;
	temp = cmd->argv;
	while (temp[i])
	{
		printf("argv[%d]: %s\n", i, temp[i]);
		i++;
	}
	printf("type: %c\n", cmd->type);
}

void	print_list(t_list *cmd)
{
	while (cmd)
	{
		print_cmd(cmd->content);
		cmd = cmd->next;
	}
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*token;
	t_list	*cmd;
	t_list	*env;

	(void)argc;
	(void)argv;
	if (!setup())
		return (1);
	env = get_env(envp);
	g_env = env;
	while (1)
	{
		print_prompt();
		if (!get_input(&line))
			continue ;
		token = to_token(line);
		cmd = to_cmd(token);
		print_list(cmd);
		fork_cmd(cmd);
	}
}
