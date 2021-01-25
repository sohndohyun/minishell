/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:44:15 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/25 20:43:08 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_list		*g_env;

t_list		*get_env(char **envp)
{
	int		pos;
	t_env	*env;
	t_list	*envs;

	argc += 0;
	argv += 0;
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
	int	i;
	char	**temp;

	temp = cmd->argv;
	i = -1;
	while (temp[++i])
		printf("argv[%d]: %s\n", i, temp[i]);
	printf("%c\n", cmd->type);
	printf("%d\n", *(cmd->pfd));
}

void	print_list(t_list *list)
{
	while (list)
	{
		print_cmd(list->content);
		list = list->next;
	}
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*token;
	t_list	*cmd;

	(void)argc;
	(void)argv;
	if (!setup())
		return (1);
	g_env = get_env(envp);
	while (1)
	{
		print_prompt();
		if (!get_input(&line))
			continue ;
		token = to_token(line);
		cmd = to_cmd(token);
		print_list(cmd);
	}
}
