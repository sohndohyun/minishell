/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:15:01 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/06 20:45:02 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nbr_length(int n)
{
	int i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	int		temp;
	char	*str;

	len = nbr_length(n);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	if (n == 0)
		str[0] = '0';
	else
	{
		i = len - 1;
		while (n != 0)
		{
			temp = n % 10;
			str[i--] = temp < 0 ? (-temp + '0') : (temp + '0');
			n /= 10;
		}
		if (i == 0)
			str[0] = '-';
	}
	str[len] = 0;
	return (str);
}
