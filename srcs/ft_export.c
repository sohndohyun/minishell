/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:06:48 by hyeonski          #+#    #+#             */
/*   Updated: 2021/01/31 10:08:38 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_export(t_env *env)
{
	ft_putstr_fd(env->key, STDOUT_FILENO);
	if (env->value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(env->value, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
	else
		ft_putendl_fd("", STDOUT_FILENO);
}

void	show_all_env(t_list *envs)
{
	while (envs)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		print_env_export(envs->content);
		envs = envs->next;
	}
}

int			check_equation(int *pos, char *str)
{
	*pos = 0;
	while (str[*pos] != '=' && str[*pos] != '\0')
		(*pos)++;
	if (*pos == 0)
		return (FALSE);
	return (TRUE);
}

void	ft_export(char **argv)
{
	t_list	*dup;
	t_env	*new;
	char	*key;
	int		pos;

	dup = ft_list_dup(g_env, ft_env_dup);
	ft_list_sort(dup, ft_env_cmp);
	if (argv == NULL || *argv++ == NULL)
		return ;
	if (*argv == NULL)
		show_all_env(dup);
	else
	{
		while (*argv)
		{
			if (is_valid_env_name(&pos, *argv) == FALSE)
			{
				print_export_error(*argv);
				argv++;
				continue;
			}
			key = ft_strndup(*argv, pos);
			if (env_valid_name(key, TRUE))
				envlst_append(lst, name, *target, locate);
			else
				export_error_handling(*target);
			if (ft_strequ(name, ENV_PATH) || ft_strequ(name, ENV_PATH_WITHPLUS))
				reset_path(path, *lst);
			free_str(&name);
			target++;
		}
	}
	ft_lstclear(&dup, free_env);
}