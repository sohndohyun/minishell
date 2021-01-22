/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:25:20 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/22 20:30:02 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_command(char **command)
{
	int		i;
	char	*temp;

	i = 0;
	while (command[i])
	{
		temp = command[i];
		command[i] = ft_strtrim(command[i], " ");
		free(temp);
		i++;
	}
}

int		has_empty_command(char **command)
{
	int		i;

	i = 0;
	while (command[i])
	{
		if (command[i] == NULL)
			return (1);
		if (ft_strcmp(command[i], "") == 0)
			return (1);
		i++;
	}
	return (0);
}

int		is_semicolon_syntax_error(char **command, char *line)
{
	int		i;
	char	*temp;

	temp = ft_strtrim(line, " ");
	if (has_empty_command(command) || temp[0] == ';')
	{
		free(temp);
		return (1);
	}
	i = -1;
	while (temp[++i])
	{
		if (temp[i] == ';' && temp[i + 1] == ';')
		{
			free(temp);
			return (1);
		}
	}
	free(temp);
	return (0);
}

char	**parse_command(char *line)
{
	char	**command;
	int		i;

	command = ft_split(line, ';');
	trim_command(command);
	i = -1;
	printf("commmand : \n");
	while (command[++i])
		printf("%d: %s$\n", i, command[i]);
	if (is_semicolon_syntax_error(command, line))
	{
		write(2, "syntax error near unexpected token `;'\n", 40);
		ft_free_2d_arr((void **)command);
		free(line);
		return (NULL);
	}
	free(line);
	return (command);
}
