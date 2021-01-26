/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:48:48 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/26 22:02:49 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(t_list *env)
{
	t_env	*oldpwd;
	t_env	*pwd;
	char	dir[4096];

	oldpwd = search_env(env, "OLDPWD");
	pwd = search_env(env, "PWD");

	if (oldpwd == NULL)
		add_env(env, ft_strdup("OLDPWD"), ft_strdup(pwd->value));
	getcwd(dir, 4096);
	modify_env(env, "PWD", ft_strdup(dir));
	
}

void	ft_cd(char **argv)
{
	char	*err_msg;

	if (argv == NULL || argv[1] == NULL)
		return ;
	if (chdir(argv[1]) == -1)
	{
		if ((err_msg = ft_strjoin("cd: ", argv[1])) == NULL)
			return ;
		print_error(err_msg, errno);
		errno = 1;
		free(err_msg);
	}
	set_pwd(g_env);
}
