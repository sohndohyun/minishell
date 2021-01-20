/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:25:20 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/20 15:28:14 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**parse_command(char *line)
{
	char	**command;
	int		i;
	char	*temp;

	command = ft_split(line, ';');
	i = 0;
	while (command[i])
	{
		temp = command[i];
		command[i] = ft_strtrim(command[i], " ");
		free(temp);
		i++;
	}
	i = 0;
	printf("commmand : \n");
	while (command[i])
		printf("%s$\n", command[i++]);
	free(line);
	return (command);
}
