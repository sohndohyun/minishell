/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 21:42:31 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/29 15:51:58 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

# define CT_NORM 1
# define CT_PIPE 2
# define TRUE 1
# define FALSE 2

typedef struct	s_cmd
{
	int			type;
	char		**argv;
	int			fd_in;
	int			fd_out;
	int			pfd[2][2];
}				t_cmd;

typedef struct	s_token_env
{
	int			status;
	char		*key;
	char		*value;
	int			value_len;
	int			idx;
	int			cmd_i;
	t_env		*env;
}				t_token_env;

int				ascii_art(void);
void			print_prompt(void);
int				get_input(char **line);
char			**parse_command(char *line);
void			trim_command(char **command);
void			handle_signal(int signo);
int				setup(void);
void			catch_ctrld(char **line);
void			ft_free_and_null(void **ptr);
char			*ft_strjoin_free_s1(char const *s1, char const *s2);
void			trim_input(char **line);
void			ft_free_2d_arr(void	 **ptr);
int				has_empty_command(char **command);
int				is_semicolon_syntax_error(char **command, char *line);
t_list*			to_cmd(t_list *token);
void			free_cmd(void *value);
int				is_redirection(char *str);
int				to_cmd_redirection_error(t_list *token);
int				to_cmd_redirection(char *type, char *value, t_cmd *cmd);
t_list*			to_token(char *str);
int				run_cmd(t_cmd *cmd);
void			fork_cmd(t_list *cmd_list);

void			ft_env(t_list *env);
void			ft_echo(char **argv);
void			ft_pwd(void);
void			ft_cd(char **argv);
void			print_error(char *msg, int errnum);
int				is_equal_key(t_env *env, char *key);
t_env			*search_env(t_list *env, char *key);
t_env			*new_env(char *key, char *value);
void			add_env(t_list *env, char *key, char *value);
void			modify_value(t_env *env, char *value);
void			modify_env(t_list *env, char *key, char *value);
int				run_cmd_builtin(t_cmd *cmd);
char	    **ft_split_token(char *str, char *set);
t_list		*to_token_in_token(char *str);


extern t_list		*g_env;

#include <stdio.h>

#endif
