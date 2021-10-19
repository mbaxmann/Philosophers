/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaxmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:33:35 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 18:24:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_act(long int time, t_philo *philo)
{
	long int	time2;

	time2 = (ft_gettime() - philo->time[1]);
	if (time2 + time >= philo->time_to_die)
	{
		ft_msleep(philo->time_to_die - time2);
		philo->is_dead = 1;
		return (1);
	}
	else
		ft_msleep(time);
	return (0);
}

void	ft_msleep(long int time)
{
	long int	curr;
	long int	time2;

	curr = ft_gettime();
	time2 = 50;
	while ((ft_gettime() - curr) < time)
	{
		usleep(time2);
	}
}

void	*ft_routine(void *param)
{
	t_philo	*philo;
	int		n;

	n = -1;
	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(20);
	if (philo->hungry)
		n = 0;
	while (!philo->is_dead && n < philo->hungry)
	{
		ft_status(philo);
	}
	ft_is_dead(philo);
	return (NULL);
}

void	ft_philo_start(void *param)
{
	int			i;
	t_data		*data;
	pthread_t	*th;

	i = 0;
	data = ((t_data *)param);
	th = (pthread_t *)malloc(sizeof(pthread_t) * (data->number));
	while (i < data->number)
	{
		pthread_create(th + i, NULL, &ft_routine, (void *)(data->philo + i));
		i++;
	}
	i = 0;
	while (i < data->number)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	ft_free(data);
	free(th);
}
