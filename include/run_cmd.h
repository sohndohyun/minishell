/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:36:08 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/06 22:38:06 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_CMD_H
# define RUN_CMD_H

# include "minishell.h"
# include <sys/stat.h>

int		is_cmd_builtin(char *cmd);
int		run_cmd_builtin_run(t_cmd *cmd);
int		run_cmd_builtin(t_cmd *cmd);
int		run_cmd_execve(t_cmd *cmd);
int		run_cmd(t_cmd *cmd, int (*run_cmd_type)(t_cmd*));
char	*find_path(char *cmd, t_list *env);
void	kvlen(char *s1, char *s2, int *key, int *value);
char	**get_envp(t_list *env_list);
int		wait_child(pid_t pid);

#endif
