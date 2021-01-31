/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 21:42:31 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/01 04:07:38 by dsohn            ###   ########.fr       */
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
t_list			*to_cmd(t_list *token);
void			free_cmd(void *value);
int				is_redirection(char *str);
int				to_cmd_redirection_error(t_list *token);
int				to_cmd_redirection(char *type, char *value, t_cmd *cmd);
t_list			*to_token(char *str);
char			*token_switch(char *token);
char			*token_remove_quote(char *token);
int				run_cmd(t_cmd *cmd, int (*run_cmd_type)(t_cmd*));
void			fork_cmd(t_list *cmd_list);
int				run_cmd_execve(t_cmd *cmd);
int				is_cmd_builtin(char *cmd);
void			ft_env(t_list *env);
void			ft_echo(char **argv);
void			ft_pwd(void);
void			ft_cd(char **argv);
void			print_error(char *msg, int errnum, char *err_val);
int				is_equal_key(t_env *env, char *key);
t_env			*search_env(t_list *env, char *key);
t_env			*new_env(char *key, char *value);
void			add_env(t_list *env, char *key, char *value);
void			modify_value(t_env *env, char *value);
void			modify_env(t_list *env, char *key, char *value);
int				run_cmd_builtin(t_cmd *cmd);
char			**ft_split_token(char *str, char *set);
t_list			*to_token_in_token(char *str);
void			ft_export(char **argv);
void			free_env(void *value);
void			*ft_env_dup(void *ref);
char			**ft_split_token(char *str, char *set);
t_list			*to_token_in_token(char *str);
int				ft_env_cmp(void *r1, void *r2);
t_list			*ft_list_dup(t_list *lst, void *(*dup)(void *));
t_list			*ft_list_sort(t_list *lst, int (*cmp)(void *, void *));
int				is_valid_env_key(char *key);
void			ft_unset(char **argv);
int				ft_exit(char **argv);
void			ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));


extern t_list	*g_env;

#include <stdio.h>

#endif
