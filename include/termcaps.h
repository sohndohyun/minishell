/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 03:50:22 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 14:26:51 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include "minishell.h"
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <termios.h>

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

void	get_cursor_position(int *col, int *rows);
void		handle_keys(long c, char **line);
void	cursor_win(void);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strjoin_middle(char *s1, const char *s2, int div);
void	print_char(long c, char **line);
void	delete_char(char **line);
char	*ft_strncat(char *s1, const char *s2, size_t n);
int		putchar_tc(int tc);
char	*ft_dups1_frees2(const char *s1, char *s2);
void	empty_space(int len);
void	up_history(char **line);
void	down_history(char **line);
void	add_cmd_to_history(char *cmd);
void	add_history_list(t_hist **begin, t_hist *new);
void	clear_history_list(t_hist **begin);
void	cut_line(char **line);
char	*ft_strjoin_middle2(char *s1, const char *s2, int div);
void	copy_line(char **line);
void	paste_line(char **line);
void	move_cursor_left(void);
void	move_cursor_right(char **line);
void	move_prev_word(char **line);
void	move_next_word(char **line);
void	move_prev_line(void);
void	move_next_line(char **line);
void	move_cursor_begin(char **line);
void	move_cursor_end(char **line);
void		print_line(long c, char **line);
void		print_line_sub(long c);

t_termcap			*g_tc;

#endif
