/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:18:51 by hyeonski          #+#    #+#             */
/*   Updated: 2020/10/07 14:18:52 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	int		index;

	if (!src)
		return (NULL);
	index = 0;
	while (src[index])
		index++;
	if (!(dup = malloc(sizeof(char) * (index + 1))))
		return (0);
	index = 0;
	while (src[index] != '\0')
	{
		dup[index] = src[index];
		index++;
	}
	dup[index] = src[index];
	return (dup);
}
