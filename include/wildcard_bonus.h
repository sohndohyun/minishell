/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:51:44 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/07 22:11:59 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_H
# define WILDCARD_BONUS_H

# include "minishell.h"

int		iswildcard(char *str);
int		ft_getargc(char **argv);
void	copy_argv(char **dst, char **src, int n);
char	**wildcard(char **argv);
char	*rd_wildcard(char *str);

#endif
