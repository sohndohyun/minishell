/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 21:42:31 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/25 20:32:08 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

int			ascii_art(void);
void		print_prompt(void);
int			get_input(char **line);
void		trim_command(char **command);
void		handle_signal(int signo);
int			setup(void);
void		catch_ctrld(char **line);
void		ft_free_and_null(void **ptr);
char		*ft_strjoin_free_s1(char const *s1, char const *s2);
void		trim_input(char **line);
void		ft_free_2d_arr(void	 **ptr);
t_list*		to_token(char *str);
t_list*		to_cmd(t_list *token);

typedef struct	s_env
{
	char	*key;
	char	*value;
}				t_env;

typedef struct	s_cmd
{
	int			type;
	char		**argv;
	int			pfd[2][2];
}				t_cmd;

#include <stdio.h>

#endif
