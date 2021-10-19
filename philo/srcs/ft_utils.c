/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaxmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:35:14 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 18:50:14 by user42           ###   ########.fr       */
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
	write(fd, str, ft_size(str));
}

void	ft_print(int mode, long int time, t_philo *philo, int *dead)
{
	char	*buffer;

	buffer = ft_itoa(time, 0);
	buffer = ft_strjoin(buffer, ft_strdup(" "));
	buffer = ft_strjoin(buffer, ft_itoa((long int)philo->id, 0));
	if (mode == 1)
		buffer = ft_strjoin(buffer, ft_strdup(" has taken a fork\n"));
	else if (mode == 2)
		buffer = ft_strjoin(buffer, ft_strdup(" is eating\n"));
	else if (mode == 3)
		buffer = ft_strjoin(buffer, ft_strdup(" is sleeping\n"));
	else if (mode == 4)
		buffer = ft_strjoin(buffer, ft_strdup(" is thinking\n"));
	if (mode != 5)
		ft_putstr_fd(buffer, 1);
	if (mode == 5)
	{
		buffer = ft_strjoin(buffer, ft_strdup(" died\n"));
		ft_putstr_fd(buffer, 1);
		*dead = 1;
		ft_msleep(philo->time_to_die);
	}
	free(buffer);
}
