/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaxmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:33:35 by user42            #+#    #+#             */
/*   Updated: 2021/10/12 15:16:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_act(long int time, t_philo *philo)
{
	if (ft_chrono(philo->time[1]) + time >= philo->time_to_die)
	{
		ft_msleep(philo->time_to_die - ft_chrono(philo->time[1]));
		philo->is_dead = 1;
		//ft_is_dead(philo);
		return (1);
	}
	else
		ft_msleep(time);
	return (0);
}

void	ft_msleep(long int time)
{
	long int curr;
	long int time2;

	curr = ft_gettime();
	time2 = time / 2;
	time2 *= 1000;
	while (ft_chrono(curr) < time)
	{
		usleep(time2);
		time2 /= 2;
		if (time2 < 1000)
			time2 = 1000;
	}
}

void	*ft_routine(void *param)
{
	t_philo	*philo;
	int		n;

	n = -1;
	philo = (t_philo *)param;
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
		i += 2;
	}
	i = 1;
	while (i < data->number)
	{
		pthread_create(th + i, NULL, &ft_routine, (void *)(data->philo + i));
		i += 2;
	}
	i = -1;
	while (++i < data->number)
		pthread_join(th[i], NULL);
	ft_free(data);
	free(th);
}

void	ft_algo(t_data *data)
{
	int	i;

	i = 0;
	data->current = 0;
	ft_philo_start(data);
}
