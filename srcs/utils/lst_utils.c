/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:27:04 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/07 00:52:22 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_list_dup(t_list *lst, void *(*dup)(void *))
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	while (lst)
	{
		new = ft_lstnew(dup(lst->content));
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}

t_list	*ft_list_sort(t_list *lst, int (*cmp)(void *, void *))
{
	t_list	*begin;
	t_list	*p;
	void	*temp;

	begin = lst;
	while (lst)
	{
		p = lst->next;
		while (p)
		{
			if ((*cmp)(lst->content, p->content) > 0)
			{
				temp = lst->content;
				lst->content = p->content;
				p->content = temp;
			}
			p = p->next;
		}
		lst = lst->next;
	}
	return (begin);
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref,
		int (*cmp)(), void (*free_fct)(void *))
{
	t_list *freedom;

	if (*begin_list)
	{
		if ((*cmp)((*begin_list)->content, data_ref) == 0)
		{
			freedom = (*begin_list);
			(*begin_list) = (*begin_list)->next;
			free_fct(freedom->content);
			free(freedom);
			ft_list_remove_if(begin_list, data_ref, cmp, free_fct);
		}
		else
			ft_list_remove_if(&(*begin_list)->next, data_ref, cmp, free_fct);
	}
}
