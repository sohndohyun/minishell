/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 00:14:41 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 00:19:03 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "../libft/libft.h"

typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

t_list	*get_env(char **envp);
void	free_env(void *value);
void	*ft_env_dup(void *ref);
int		ft_env_cmp(void *r1, void *r2);
t_env	*new_env(char *key, char *value);
int		is_equal_key(t_env *env, char *key);
t_env	*search_env(t_list *env, char *key);
void	modify_value(t_env *env, char *value);
void	modify_env(t_list *env, char *key, char *value);
void	add_env(t_list *env, char *key, char *value);

#endif