/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:25:25 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/05 12:08:03 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cursor_position(int *col, int *rows)
{
	int		a;
	int		i;
	char	buf[255];
	int		ret;

	a = 0;
	i = 1;
	write(STDIN_FILENO, "\033[6n", 4);
	ret = read(STDIN_FILENO, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = ft_atoi(&buf[i]) - 1;
			else
				*col = ft_atoi(&buf[i]) - 1;
			a++;
			i += ft_nbr_length(*col) - 1;
		}
		i++;
	}
}
