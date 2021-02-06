#ifndef TEMP_H
# define TEMP_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <glob.h>
# include "../libft/libft.h"

# define BACKSPACE 127
# define EOF_KEY 4
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699

# define HOME 4741915
# define END 4610843

# define ALT_X 8948194
# define ALT_C 42947
# define ALT_V 10127586

# define CTRL_LEFT 74995417045787
# define CTRL_RIGHT 73895905418011
# define CTRL_UP 71696882162459
# define CTRL_DOWN 72796393790235

typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

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

typedef struct		s_hist
{
	char			*cmd;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_termcap
{
	struct termios	term;
	struct termios	term_backup;
	t_hist			*history;
	t_hist			*cur_history;
	char			*backup_cmd;
	char			*copy_cmd;
	int				start_row;
	int				start_col;
	int				col;
	int				row;
	int				plen;
	int				cur_pos;
	int				currow;
	int				curcol;
	int				lenlen;
	int				rowoffset;
	int				mod_offset;
	int				endcol;
	int				endrow;
	char			*cm;
	char			*ce;
	char			*dl;
	long			backspace;
}					t_termcap;

extern t_list		*g_env;
extern t_termcap	*g_tc;


/*
** Src is : ../srcs/get_input.c
*/
void	catch_ctrld(char **line);
int		get_input(char **line);

/*
** Src is : ../srcs/str_utils.c
*/
char	*ft_strjoin_middle(char *s1, const char *s2, int div);
char	*ft_strjoin_middle2(char *s1, const char *s2, int div);
char	*ft_strncat(char *s1, const char *s2, size_t n);
char	*ft_strcat(char *dst, const char *src);
char	*ft_dups1_frees2(const char *s1, char *s2);

/*
** Src is : ../srcs/cmd_line_io_bonus.c
*/
void	print_char(long c, char **line);
void	delete_char(char **line);
void	cut_line(char **line);
void	copy_line(char **line);
void	paste_line(char **line);

/*
** Src is : ../srcs/ft_echo.c
*/
int		ft_echo(char **argv);

/*
** Src is : ../srcs/to_cmd.c
*/
int		get_argv_len(t_list *token);
char	**parse_argv(t_list **token, t_cmd *cmd);
void	parse_type_token(t_list **token, t_cmd *cmd);
int		check_cmd_bucket(t_list *cmd);
t_list	*to_cmd(t_list *token);

/*
** Src is : ../srcs/cursor_bonus.c
*/
void	move_cursor_left(void);
void	move_cursor_right(char **line);
void	get_cursor_position(int *col, int *rows);

/*
** Src is : ../srcs/termcap_utils_bonus.c
*/
void	cursor_win(void);
int		putchar_tc(int tc);
void	empty_space(int len);

/*
** Src is : ../srcs/print_prompt_bonus.c
*/
int		ascii_art(void);
void	print_prompt(void);

/*
** Src is : ../srcs/cursor_line_bonus.c
*/
void	move_prev_line(void);
void	move_next_line(char **line);
void	move_cursor_begin(char **line);
void	move_cursor_end(char **line);

/*
** Src is : ../srcs/init.c
*/
int		setup(void);
t_list	*get_env(char **envp);

/*
** Src is : ../srcs/signal_handle.c
*/
void	handle_signal_main(int signo);
void	handle_signal_chlid(int signo);

/*
** Src is : ../srcs/signal_handle_bonus.c
*/
void	handle_signal_main(int signo);
void	handle_signal_chlid(int signo);

/*
** Src is : ../srcs/to_token.c
*/
t_list	*to_token(char *str);

/*
** Src is : ../srcs/utils.c
*/
void	ft_free_and_null(void **ptr);
void	ft_free_2d_arr(void **ptr);
char	*ft_strjoin_free_s1(char const *s1, char const *s2);
int		ft_nbr_length(int n);
void	free_strarr(char **arr);

/*
** Src is : ../srcs/ft_cd.c
*/
void	set_pwd(t_list *env);
int		ft_cd(char **argv);

/*
** Src is : ../srcs/run_cmd.c
*/
int		is_cmd_builtin(char *cmd);
int		run_cmd_builtin_run(t_cmd *cmd);
int		run_cmd_builtin(t_cmd *cmd);
int		run_cmd_execve(t_cmd *cmd);
int		run_cmd(t_cmd *cmd, int (*run_cmd_type)(t_cmd*));

/*
** Src is : ../srcs/ft_unset.c
*/
int		print_unset_error(char *id);
int		ft_unset(char **argv);

/*
** Src is : ../srcs/error.c
*/
void	print_error(char *msg, int errnum, char *err_val);
t_list	*handle_syntax_error(t_list **list, char *str);
char	**print_file_error(int i, char **argv, char *file_name);
char	**cmd_syntax_error(void);

/*
** Src is : ../srcs/wildcard_bonus.c
*/
void	wildcard_inloop(char **argv, int i, int *argc);
char	**wildcard(char **argv);
char	*rd_wildcard(char *str);

/*
** Src is : ../srcs/to_token_utils.c
*/
int		get_key_length(char *key);
char	*find_value(char *str, int n);
char	*token_remove_quote(char *token);
void	switch_value(char **ret, char **it, char **save);
char	*token_switch(char *token);

/*
** Src is : ../srcs/ft_env.c
*/
void	print_env(t_env *env);
int		ft_env(t_list *env);

/*
** Src is : ../srcs/print_prompt.c
*/
int		ascii_art(void);
void	print_prompt(void);

/*
** Src is : ../srcs/history_bonus.c
*/
void	up_history(char **line);
void	down_history(char **line);
void	add_cmd_to_history(char *cmd);
void	add_history_list(t_hist **begin, t_hist *new);
void	clear_history_list(t_hist **begin);

/*
** Src is : ../srcs/ft_pwd.c
*/
int		ft_pwd(void);

/*
** Src is : ../srcs/init_bonus.c
*/
int		setup(void);
t_list	*get_env(char **envp);
void	init_term(void);
void	init_tc(void);
void	reinit_termcap(void);

/*
** Src is : ../srcs/ft_exit.c
*/
int		ft_exit(char **argv);

/*
** Src is : ../srcs/lst_utils.c
*/
t_list	*ft_list_dup(t_list *lst, void *(*dup)(void *));
t_list	*ft_list_sort(t_list *lst, int (*cmp)(void *, void *));
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

/*
** Src is : ../srcs/to_cmd_redirection.c
*/
void	catch_ctrld_heredoc(char **line);
int		get_herdoc_input(char **line);
int		here_document(char *value);
int		to_cmd_redirection(char *type, char *value, t_cmd *cmd);

/*
** Src is : ../srcs/to_cmd_redirection_util.c
*/
int		is_redirection(char *str);
int		to_cmd_redirection_error(t_list *token);

/*
** Src is : ../srcs/ft_export.c
*/
void	print_env_export(t_env *env);
int		show_all_env(t_list *envs);
int		print_export_error(char *equation);
int		ft_export_add_env(char **argv);
int		ft_export(char **argv);

/*
** Src is : ../srcs/env_utils.c
*/
int		is_equal_key(t_env *env, char *key);
t_env	*search_env(t_list *env, char *key);
void	modify_value(t_env *env, char *value);
void	modify_env(t_list *env, char *key, char *value);
void	add_env(t_list *env, char *key, char *value);

/*
** Src is : ../srcs/run_cmd_util.c
*/
char	*find_path(char *cmd, t_list *env);
void	kvlen(char *s1, char *s2, int *key, int *value);
char	**get_envp(t_list *env_list);
int		wait_child(pid_t pid);

/*
** Src is : ../srcs/cursor_word_bonus.c
*/
void	move_prev_word(char **line);
void	move_next_word(char **line);

/*
** Src is : ../srcs/to_cmd_utils.c
*/
int		is_type_token(char *str);
void	free_cmd(void *value);
t_cmd	*new_cmd(void);
int		check_cmd_syntax(t_list *cmd);
t_list	*clear_cmd(t_cmd *cmd, t_list *cmd_list, t_list *token);

/*
** Src is : ../srcs/wildcard_util_bonus.c
*/
int		iswildcard(char *str);
int		ft_getargc(char **argv);
void	copy_argv(char **dst, char **src, int n);

/*
** Src is : ../srcs/ft_export_utils.c
*/
int		check_first_equal_char(int *pos, char *str);
int		is_valid_env_key(char *key);

/*
** Src is : ../srcs/get_input_bonus.c
*/
void	handle_move_keys(long c, char **line);
void	print_line(long c, char **line);
void	print_line_sub(long c);
void	handle_keys(long c, char **line);
int		get_input(char **line);

/*
** Src is : ../srcs/env_control.c
*/
void	free_env(void *value);
void	*ft_env_dup(void *ref);
int		ft_env_cmp(void *r1, void *r2);
t_env	*new_env(char *key, char *value);

/*
** Src is : ../srcs/fork_cmd.c
*/
void	fork_run_cmd(t_cmd *cmd, int *status, int save_in, int save_out);
t_list	*find_cmd_end(t_list *cmd_list);
void	fork_cmd(t_list *cmd_list);

#endif
