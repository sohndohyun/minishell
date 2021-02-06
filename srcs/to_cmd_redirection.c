/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 03:13:55 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/06 20:20:16 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_redirection(char *str)
{
	return (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0 ||
		ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0);
}

int		to_cmd_redirection_error(t_list *token)
{
	if(!token->next)
		return (1);
	token = token->next;
	if (is_redirection(token->content) ||
		ft_strcmp(token->content, "|") == 0 ||
		ft_strcmp(token->content, ";") == 0)
		return (1);
	return (0);
}

void	catch_ctrld_hd(char **line)
{
	char	*line_buf;
	int		flag_exit;

	line_buf = ft_strdup("");
	flag_exit = 1;
	while (get_next_line(STDIN_FILENO, line) == 0)
	{
		line_buf = ft_strjoin_free_s1(line_buf, *line);
		if (**line == '\0' && flag_exit == 1)
		{
			free(*line);
			free(line_buf);
			write(1, "exit\n", 6);
			exit(EXIT_SUCCESS);
		}
		write(1, "  \b\b", 4);
		free(*line);
		flag_exit = 0;
	}
	if (flag_exit == 0)
	{
		free(*line);
		*line = ft_strdup(line_buf);
	}
	free(line_buf);
}

int		get_input_hd(char **line)
{
	catch_ctrld_hd(line);
	if (*line == NULL || ft_strcmp(*line, "") == 0)
	{
		free(*line);
		return (0);
	}
	return (1);
}

int		here_document(char *value)
{
	char *line;
	char *doc;
	int ret;
	int fds[2];

	pipe(fds);
	doc = ft_strdup("");
	while (1)
	{
		write(1, "> ", 2);
		ret = get_input_hd(&line);
		if (ret)
		{
			if (ft_strcmp(value, line) == 0)
			{
				free(line);
				break ;
			}
			doc = ft_strjoin_free_s1(doc, line);
			free(line);
		}
		doc = ft_strjoin_free_s1(doc, "\n");
	}
	ft_putstr_fd(doc, fds[1]);
	free(doc);
	close(fds[1]);
	return (fds[0]);
}

int		to_cmd_redirection(char *type, char *value, t_cmd *cmd)
{
	char *wc;

	if (!type || !value)
		return (0);
	if (ft_strcmp(type, "<<") == 0)
	{
		cmd->fd_in = here_document(value);
		return (1);
	}
	
	wc = rd_wildcard(value);
	if (wc == NULL)
		return (0);
	if (ft_strcmp(type, "<") == 0)
	{
		cmd->fd_in = open(wc, O_RDONLY);
		free(wc);
		if (cmd->fd_in < 0)
			return (0);
		return (1);
	}
	else if (ft_strcmp(type, ">") == 0)
	{
		cmd->fd_out = open(wc, O_WRONLY | O_CREAT, 0644);
		free(wc);
		if (cmd->fd_out < 0)
			return (0);
		return (1);
	}
	else
	{
		cmd->fd_out = open(wc, O_WRONLY | O_APPEND, 0644);
		free(wc);
		if (cmd->fd_out < 0)
			return (0);
		return (1);
	}
}
