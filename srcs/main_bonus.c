/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:44:15 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/05 12:04:51 by hyeonski         ###   ########.fr       */
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
	init_term();
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

void	init_term(void)
{
	t_env	*env;

	if (!(env = search_env(g_env, "TERM")))
		env->value = "xterm";
	tgetent(NULL, env->value);
	setupterm(NULL, STDOUT_FILENO, NULL);
	tcgetattr(0, &g_tc->term);
	tcgetattr(0, &g_tc->term_backup);
	g_tc->term.c_lflag = g_tc->term.c_lflag & ~ICANON;
	g_tc->term.c_lflag = g_tc->term.c_lflag & ~ECHO;
	g_tc->term.c_cc[VMIN] = 1;
	g_tc->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_tc->term);
	init_tc();
}

void	init_tc(void)
{
	g_tc->cm = tgetstr("cm", NULL);
	g_tc->ce = tgetstr("ce", NULL);
	g_tc->dl = tgetstr("DL", NULL);
}


int		main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*token;
	t_list	*cmd;
	t_list	*env;
	t_termcap	termcap;

	(void)argc;
	(void)argv;
	env = get_env(envp);
	g_env = env;
	g_tc = &termcap;
	ft_bzero(&termcap, sizeof(t_termcap));
	if (!setup())
		return (1);
	line = NULL;
	while (1)
	{
		signal(SIGINT, (void *)handle_signal_main);
		signal(SIGQUIT, (void *)handle_signal_main);
		get_cursor_position(&g_tc->start_col, &g_tc->start_row);
		print_prompt();
		get_cursor_position(&g_tc->col, &g_tc->start_row);
		g_tc->mod_offset = 0;
		if (get_input(&line))
		{
			tcsetattr(0, TCSANOW, &g_tc->term_backup);
			add_cmd_to_history(line);
			if (!(token = to_token(line)) || !(cmd = to_cmd(token)))
				continue ; //syntax error!
			ft_free_and_null((void **)&line);
			ft_lstclear(&token, free);
			fork_cmd(cmd);
			ft_lstclear(&cmd, free_cmd);
		}
	}
}
