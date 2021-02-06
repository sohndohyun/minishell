/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:51:44 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/06 23:53:43 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_H
# define WILDCARD_BONUS_H

# include "minishell.h"

int		iswildcard(char *str);
int		ft_getargc(char **argv);
void	copy_argv(char **dst, char **src, int n);
void	wildcard_inloop(char **argv, int i, int *argc);
char	**wildcard(char **argv);
char	*rd_wildcard(char *str);

#endif
