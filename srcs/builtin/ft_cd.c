/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:48:48 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 00:49:27 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

void	set_pwd(t_list *env)
{
	t_env	*oldpwd;
	t_env	*pwd;
	char	dir[4096];

	oldpwd = search_env(env, "OLDPWD");
	pwd = search_env(env, "PWD");
	getcwd(dir, 4096);
	modify_env(env, "OLDPWD", ft_strdup(pwd->value));
	modify_env(env, "PWD", ft_strdup(dir));
}

int		ft_cd(char **argv)
{
	char	*err_msg;

	if (argv == NULL || argv[1] == NULL)
		return (1);
	if (chdir(argv[1]) == -1)
	{
		if ((err_msg = ft_strjoin("cd: ", argv[1])) == NULL)
			return (1);
		print_error(err_msg, errno, strerror(errno));
		errno = 1;
		free(err_msg);
		return (errno);
	}
	set_pwd(g_env);
	return (0);
}
