/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 19:11:54 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/08 01:05:50 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

void	print_error(char *msg, int errnum, char *err_val)
{
	if (errnum == -1)
		errnum = errno;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(err_val, STDERR_FILENO);
}

t_list	*handle_syntax_error(t_list **list, char *str)
{
	ft_lstclear(list, free);
	ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
	errno = 258;
	ft_free_and_null((void **)&str);
	return (NULL);
}

char	**print_file_error(int i, char **argv, char *file_name)
{
	while (--i >= 0)
		free(argv[i]);
	free(argv);
	errno = 2;
	print_error(file_name, 2, strerror(2));
	return (NULL);
}

char	**cmd_syntax_error(void)
{
	ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
	errno = 258;
	return (NULL);
}

t_list	*handle_cmd_syntax_error(t_list **list, void (*free_fct)(void *))
{
	ft_lstclear(list, free_fct);
	ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
	errno = 258;
	return (NULL);
}
