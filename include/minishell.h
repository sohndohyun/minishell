/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 00:31:43 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 22:23:13 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <glob.h>
# include <string.h>
# include "../libft/libft.h"

# define CT_CMD 0
# define CT_SEMI 1
# define CT_PIPE 2
# define CT_AND 3
# define CT_OR 4
# define CT_BEGIN 5
# define CT_END 6

typedef struct	s_cmd
{
	int			type;
	char		**argv;
	int			fd_in;
	int			fd_out;
	int			pfd[2][2];
}				t_cmd;

typedef struct	s_bigcmd
{
	int			type;
	char		*cmdstr;
}				t_bigcmd;

extern t_list	*g_env;

void			print_prompt(void);
int				setup(void);
void			init_term(void);
void			init_tc(void);
void			reinit_termcap(void);

void			handle_signal_main(int signo);
void			handle_signal_chlid(int signo);
void			handle_signal_main(int signo);
void			handle_signal_chlid(int signo);

void			catch_ctrld(char **line);
int				get_input(char **line);
void			print_char(long c, char **line);
void			delete_char(char **line);
void			cut_line(char **line);
void			copy_line(char **line);
void			paste_line(char **line);

t_list			*to_token(char *str);
int				get_key_length(char *key);
char			*find_value(char *str, int n);
char			*token_remove_quote(char *token);
void			switch_value(char **ret, char **it, char **save);
char			*token_switch(char *token);

t_list			*to_cmd(t_list *token);
t_cmd			*new_cmd(void);
int				is_type_token(char *str);
t_list			*clear_cmd(t_cmd *cmd, t_list *cmd_list, t_list *token);
int				check_cmd_syntax(t_list *cmd);
int				is_redirection(char *str);
int				to_cmd_redirection(char *type, char *value, t_cmd *cmd);
int				to_cmd_redirection_error(t_list *token);
void			catch_ctrld_heredoc(char **line);
int				get_herdoc_input(char **line);
int				here_document(char *value);
int				get_argv_len(t_list *token);
void			kvlen(char *s1, char *s2, int *key, int *value);

void			fork_cmd(t_list *cmd_list);
int				is_cmd_builtin(char *cmd);
int				run_cmd_builtin(t_cmd *cmd);
int				run_cmd_builtin_run(t_cmd *cmd);
int				run_cmd_execve(t_cmd *cmd);
int				run_cmd(t_cmd *cmd, int (*run_cmd_type)(t_cmd*));
int				wait_child(pid_t pid);
char			*find_path(char *cmd, t_list *env);
char			**get_envp(t_list *env_list);

void			free_cmd(void *value);

int				ft_cd(char **argv);
int				ft_echo(char **argv);
int				ft_env(t_list *env);
int				ft_exit(char **argv);
int				ft_export(char **argv);
int				ft_pwd(void);
int				ft_unset(char **argv);

int				check_first_equal_char(int *pos, char *str);
int				is_valid_env_key(char *key);

void			print_error(char *msg, int errnum, char *err_val);
t_list			*handle_syntax_error(t_list **list, char *str);
char			**print_file_error(int i, char **argv, char *file_name);
char			**cmd_syntax_error(void);
t_list			*handle_cmd_syntax_error(t_list **list, void (*free_fct)(void *));

t_list			*to_bigtoken(char *str);
t_list			*to_bigcmd(t_list *bigtoken);
void			run_bigcmd(t_list *cmd_list);
void			free_bigcmd(void *value);

#endif
