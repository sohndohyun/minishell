/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:53:04 by dsohn             #+#    #+#             */
/*   Updated: 2021/01/29 03:10:45 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		find_next_ch(char *str, char c)
{
	char *temp;

	temp = str + 1;
	while (*temp)
	{
		if (*temp == c && *(temp - 1) != '\\')
			return (temp - str);
		temp++;
	}
	return (-1);
}

static int		need_seperate(char c)
{
	return (ft_isspace(c) || c == '<' || c == '>'
			|| c == '\'' || c == '\"' || c == '|' || c == ';');
}

static int		find_token_non_end(char *str)
{
	char *temp;

	temp = str + 1;
	while (*temp)
	{
		if (need_seperate(*temp) && *(temp - 1) != '\\')
			break ;
		temp++;
	}
	return (temp - str);
}

static int		find_token_length(char *str)
{
	int		imsi;

	if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
		return (2);
	else if (*str == '<' || *str == '|' || *str == '>' || *str == ';')
		return (1);
	else if (*str == '\'' || *str == '\"')
	{
		imsi = find_next_ch(str, *str);
		return (imsi != -1 ? imsi + 1 : -1);
	}
	return (find_token_non_end(str));
}

void			switch_token(char **token)
{
	int		i;
	char	*temp;
	char	*key;
	char	*value;
	t_env	*env;
	
	i = 0;
	while (token[i])
	{
		temp = token[i];
		if (*temp == '$')
		{
			key = ft_substr(temp, 1, ft_strlen(temp) - 1);
			env = search_env(g_env, key);
			if (env != NULL)
				value = ft_strdup(env->value);
			else
				value = ft_strdup("");
			token[i] = value;
			free(temp);
			free(key);
		}
		i++;
	}
}

char			*switch_env(char *str)
{
	char	**token;
	int		i;
	char	*result;

	token = ft_split_token(str, " \'\"");
	switch_token(token);
	result = ft_strdup("");
	i = 0;
	while (token[i])
		result = ft_strjoin_free_s1(result, token[i++]);
	ft_free_2d_arr((void **)token);
	return (result);
}

void			refine_token(t_list **begin_list)
{
	char	*str;
	char	*temp;
	t_list	*new_token;
	t_list	*curr;
	t_list	*prev;

	prev = NULL;
	curr = *begin_list;
	while (curr)
	{
		str = curr->content;
		if (*str == '\'')
		{
			temp = ft_strtrim(str, "\'");
			free(str);
			curr->content = temp;
		}
		else if (*str == '\"')
		{
			temp = ft_strtrim(str, "\"");
			free(str);
			str = switch_env(temp);
			free(temp);
			curr->content = str;
		}
		else
		{
			temp = switch_env(str);
			free(str);
			new_token = to_token_in_token(temp);
			if (prev != NULL)
				prev->next = new_token;
			else
				*begin_list = new_token;
			new_token = ft_lstlast(new_token);
			new_token->next = curr->next;
			free(curr);
			curr = new_token;
		}
		prev = curr;
		curr = curr->next;
	}
}

t_list			*to_token_in_token(char *str)
{
	t_list	*list;
	int		token_len;
	char	*temp;

	list = NULL;
	while (*str)
	{
		if (ft_isspace(*str))
			str++;
		else
		{
			token_len = find_token_length(str);
			temp = malloc(token_len + 1);
			temp[token_len] = '\0';
			ft_strlcpy(temp, str, token_len + 1);
			ft_lstadd_back(&list, ft_lstnew(temp));
			str += token_len;
		}
	}
	if (list == NULL)
		list = ft_lstnew(ft_strdup(""));
	return (list);
}

t_list			*to_token(char *str)
{
	t_list	*list;
	int		token_len;
	char	*temp;

	list = NULL;
	while (*str)
	{
		if (ft_isspace(*str))
			str++;
		else
		{
			token_len = find_token_length(str);
			if (token_len == -1)
			{
				ft_lstclear(&list, free);
				ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
				return (NULL);
			}
			temp = malloc(token_len + 1);
			temp[token_len] = '\0';
			ft_strlcpy(temp, str, token_len + 1);
			ft_lstadd_back(&list, ft_lstnew(temp));
			str += token_len;
		}
	}
	refine_token(&list);
	return (list);
}
