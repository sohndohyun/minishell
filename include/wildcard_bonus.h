/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:29:26 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/06 21:33:02 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_H
# define WILDCARD_BONUS_H

# include <glob.h>

void	copy_argv(char **dst, char **src, int n);
int		ft_getargc(char **argv);
int		iswildcard(char *str);
char	*rd_wildcard(char *str);
char	**wildcard(char **argv);

#endif