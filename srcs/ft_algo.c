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

int	ft_act(int act, t_philo *philo)
{
	long long int	i;
	long long int	time;
	long long int	time2;

	i = 0;
	if (act == 0)
		time = philo->time_to_eat;
	else
		time = philo->time_to_sleep;
	time2 = ft_gettime();
	while (ft_chrono(time2) < time)
	{
		ft_usleep(1000);
		i++;
		if (ft_chrono(philo->time[1]) > philo->time_to_die)
		{
			return (1);
		}
	}
	return (0);
}

void	ft_usleep(int time)
{
	int	count;

	count = 0;
	while (count < time)
	{
		usleep(time / 10);
		count += (time / 10);
	}
}

void	*ft_routine(void *param)
{
	t_philo	*philo;
	int		i;
	int		n;

	i = 0;
	n = -1;
	philo = (t_philo *)param;
	if ((philo->id % 2) == 1)
		ft_usleep(1000);
	philo->time[1] = ft_gettime();
	if (philo->hungry)
		n = 0;
	while (!philo->is_dead && n < philo->hungry)
	{
		ft_status(philo, i);
		ft_is_dead(philo);
		i++;
		i %= 5;
	}
	return (NULL);
}

void	ft_philo_start(void *param)
{
	int			i;
	t_data		*data;
	pthread_t	*th;

	i = 1;
	data = ((t_data *)param);
	th = (pthread_t *)malloc(sizeof(pthread_t) * (data->number));
	pthread_mutex_init(&data->lock, NULL);
	while (i < data->number)
	{
		pthread_create(th + i, NULL, &ft_routine, (void *)(data->philo + i));
		i += 2;
	}
	i = 0;
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
