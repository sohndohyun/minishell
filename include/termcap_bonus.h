/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 00:01:44 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 00:29:47 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAP_BONUS_H
# define TERMCAP_BONUS_H

#include "history_bonus.h"
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
void	cursor_win(void);
int		putchar_tc(int tc);
void	empty_space(int len);
void	move_cursor_left(void);
void	move_cursor_right(char **line);
void	move_prev_line(void);
void	move_next_line(char **line);
void	move_cursor_begin(char **line);
void	move_cursor_end(char **line);
void	move_prev_word(char **line);
void	move_next_word(char **line);

extern t_termcap	*g_tc;

#endif