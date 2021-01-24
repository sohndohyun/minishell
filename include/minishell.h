/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 21:42:31 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/25 03:51:10 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

int		ascii_art(void);
void	print_prompt(void);
int		get_input(char **line);
char	**parse_command(char *line);
void	trim_command(char **command);
void	handle_signal(int signo);
int		setup(void);
void	catch_ctrld(char **line);
void	ft_free_and_null(void **ptr);
char	*ft_strjoin_free_s1(char const *s1, char const *s2);
void	trim_input(char **line);
void	ft_free_2d_arr(void	 **ptr);
int		has_empty_command(char **command);
int		is_semicolon_syntax_error(char **command, char *line);
t_list*		to_token(char *str);

typedef struct	s_env
{
	char	*key;
	char	*value;
}				t_env;

# define CT_NORM 1
# define CT_PIPE 2

typedef struct	s_cmd
{
	int	type;
	char	**argv;
	int	**pfd;
}		t_cmd;

#include <stdio.h>

#endif
