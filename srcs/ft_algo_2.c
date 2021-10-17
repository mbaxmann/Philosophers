/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaxmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:33:54 by user42            #+#    #+#             */
/*   Updated: 2021/10/12 15:17:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_is(t_philo *philo, int i)
{
	long int	time;

	time = ft_gettime() - philo->time[0];
	if (!ft_is_dead(philo))
	{
		pthread_mutex_lock(philo->write);
		ft_print(i, time, philo);
		pthread_mutex_unlock(philo->write);
	}
}

int	ft_status_p1(t_philo *philo, int i)
{
	if (i == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		ft_is(philo, 1);
		if (!philo->right_fork)
		{
			ft_msleep(philo->time_to_die);
			pthread_mutex_unlock(&philo->left_fork);
			ft_is_dead(philo);
			return (1);
		}
		pthread_mutex_lock(philo->right_fork);
		ft_is(philo, 1);
	}
	else if (i == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_is(philo, 1);
		pthread_mutex_lock(&philo->left_fork);
		ft_is(philo, 1);
	}
	return (0);
}

int	ft_status_p2(t_philo *philo)
{
	philo->time[1] = ft_gettime();
	ft_is(philo, 2);
	if (ft_act(philo->time_to_eat, philo))
		return (1);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_is(philo, 3);
	if (ft_act(philo->time_to_sleep, philo))
		return (1);
	if (philo->hungry)
		philo->hungry--;
	philo->round++;
	ft_is(philo, 4);
	return (0);
}

void	ft_status(t_philo *philo)
{
	int i;

	if ((philo->id + philo->round) % 2 == 0)
		i = 1;
	else
		i = 0;	
	ft_status_p1(philo, i);
	ft_status_p2(philo);
}
