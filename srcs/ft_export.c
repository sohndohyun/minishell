/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:06:48 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/02 00:35:08 by hyeonski         ###   ########.fr       */
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

int		show_all_env(t_list *envs)
{
	while (envs)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		print_env_export(envs->content);
		envs = envs->next;
	}
	return (0);
}

int			check_first_equal_char(int *pos, char *str)
{
	*pos = 0;
	while (str[*pos] != '=' && str[*pos] != '\0')
		(*pos)++;
	if (*pos == 0)
		return (0);
	return (1);
}

int				is_valid_env_key(char *key)
{
	int			is_first;

	if (!key)
		return (0);
	is_first = 1;
	while (*key)
	{
		if (is_first == 1 && ft_isdigit(*key))
			return (0);
		if (!ft_isalnum(*key) && *key != '_')
		{
			if (*key == '+' && *(key + 1) == '\0')
				return (1);
			return (0);
		}
		key++;
		is_first = 0;
	}
	return (1);
}

int		print_export_error(char *equation)
{
	char	*temp;
	char	*err_msg;

	errno = 1;
	if ((temp = ft_strjoin("export: `", equation)) == NULL)
		return (errno);
	err_msg = ft_strjoin_free_s1(temp, "\'");
	if (err_msg == NULL)
		return (errno);
	print_error(err_msg, -1, "not a valid identifier");
	free(err_msg);
	return (errno);
}

int		ft_export_add_env(char **argv)
{
	int		pos;
	char	*key;
	char	*value;
	
	while (*argv)
	{
		if (!check_first_equal_char(&pos, *argv))
		{
			return (print_export_error(*argv));
			argv++;
			continue;
		}
		key = ft_substr(*argv, 0, pos);
		if (is_valid_env_key(key))
		{
			if (ft_strchr(*argv, '='))
				value = ft_substr(*argv, pos + 1, ft_strlen(*argv) - pos - 1);
			else
				value = NULL;
			add_env(g_env, key, value);
		}
		else
			return (print_export_error(*argv));
		argv++;
	}
	return (0);
}

int		ft_export(char **argv)
{
	t_list	*dup;
	int		status;
	
	status = 0;
	dup = ft_list_dup(g_env, ft_env_dup);
	ft_list_sort(dup, ft_env_cmp);
	if (argv == NULL || *argv++ == NULL)
		return (0);
	if (*argv == NULL)
		status = show_all_env(dup);
	else
		status = ft_export_add_env(argv);
	ft_lstclear(&dup, free_env);
	return (status);
}