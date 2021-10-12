/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaxmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:35:14 by user42            #+#    #+#             */
/*   Updated: 2021/10/12 14:35:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_isminus(char c, int *i)
{
	if (c == '-')
	{
		(*i)++;
		return (-1);
	}
	else
	{
		(*i)++;
		return (1);
	}
}

int	ft_atoi(const char *str)
{
	int			i;
	int			min;
	long int	res;

	i = 0;
	min = 1;
	res = 0;
	while (str[i])
	{
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			i++;
		if (str[i] == '-' || str[i] == '+')
			min = ft_isminus(str[i], &i);
		while (str[i] >= '0' && str[i] <= '9' && res * 10 < 2147483648)
			res = res * 10 + (str[i++] - '0');
		if ((res > 2147483648 || (str[i] >= '0' && str[i] <= '9')) && min == -1)
			return (-1);
		if ((res > 2147483647 || (str[i] >= '0' && str[i] <= '9')) && min == 1)
			return (-1);
		return (res * min);
	}
	return (res * min);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}
