/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 00:03:43 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 01:48:57 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_BONUS_H
# define HISTORY_BONUS_H

typedef struct		s_hist
{
	char			*cmd;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

void				up_history(char **line);
void				down_history(char **line);
void				add_cmd_to_history(char *cmd);
void				add_history_list(t_hist **begin, t_hist *new);
void				clear_history_list(t_hist **begin);

#endif
