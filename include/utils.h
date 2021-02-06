/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 00:07:43 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 01:51:32 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"

/*
** Src is : ../srcs/str_utils.c
*/
char	*ft_strjoin_middle(char *s1, const char *s2, int div);
char	*ft_strjoin_middle2(char *s1, const char *s2, int div);
char	*ft_strncat(char *s1, const char *s2, size_t n);
char	*ft_strcat(char *dst, const char *src);
char	*ft_dups1_frees2(const char *s1, char *s2);

/*
** Src is : ../srcs/utils.c
*/
void	ft_free_and_null(void **ptr);
void	ft_free_2d_arr(void **ptr);
char	*ft_strjoin_free_s1(char const *s1, char const *s2);
int		ft_nbr_length(int n);
void	free_strarr(char **arr);

/*
** Src is : ../srcs/lst_utils.c
*/
t_list	*ft_list_dup(t_list *lst, void *(*dup)(void *));
t_list	*ft_list_sort(t_list *lst, int (*cmp)(void *, void *));
void	ft_list_remove_if(t_list **begin_list,
	void *data_ref, int (*cmp)(), void (*free_fct)(void *));

#endif
