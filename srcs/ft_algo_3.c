/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaxmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:34:20 by user42            #+#    #+#             */
/*   Updated: 2021/10/12 14:34:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	ft_gettime(void)
{
	struct timeval	time;
	long int	first;

	gettimeofday(&time, NULL);
	first = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (first);
}

long int	ft_chrono(long int last)
{
	return (ft_gettime() - last);
}

int	ft_is_dead(t_philo *philo)
{
	static int		dead = 0;

	pthread_mutex_lock(philo->write);
	if (ft_chrono(philo->time[1]) >= philo->time_to_die)
	{
		philo->is_dead = 1;
		if (!dead)
		{
			ft_print(5, ft_chrono(philo->time[0]), philo);
			dead = 1;
		}
		pthread_mutex_unlock(philo->write);
		return (1);
	}
	pthread_mutex_unlock(philo->write);
	return (0);
}
