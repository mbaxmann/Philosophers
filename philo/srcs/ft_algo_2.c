/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaxmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:33:54 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 19:38:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_is(t_philo *philo, int i)
{
	long int	time;

	if (!ft_is_dead(philo))
	{
		time = ft_gettime() - philo->time[0];
		pthread_mutex_lock(philo->write);
		ft_print(i, time, philo, NULL);
		pthread_mutex_unlock(philo->write);
	}
	else
		return (1);
	return (0);
}

int	ft_status_p1(t_philo *philo, int i)
{
	if (i == 0)
	{
		if (ft_is_dead(philo))
                        return (1);

		pthread_mutex_lock(&philo->left_fork);
		if (ft_is(philo, 1))
			pthread_mutex_unlock(philo->right_fork);
		if (!philo->right_fork)
		{
			ft_msleep(philo->time_to_die);
			ft_is_dead(philo);
			return (1);
		}
		pthread_mutex_lock(philo->right_fork);
		if (ft_is(philo, 1))
			ft_unlock(philo);
	}
	else if (i == 1)
	{
		if (ft_is_dead(philo))
                        return (1);

		pthread_mutex_lock(philo->right_fork);
		if (ft_is(philo, 1))
			pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
		if (ft_is(philo, 1))
			ft_unlock(philo);
	}
	return (0);
}

int	ft_status_p2(t_philo *philo)
{
	ft_is(philo, 2);
	philo->time[1] = ft_gettime();
	if (ft_act(philo->time_to_eat, philo))
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_is(philo, 3);
	if (ft_act(philo->time_to_sleep, philo))
		return (1);
	if (philo->hungry)
		philo->hungry--;
	(philo->round)++;
	ft_is(philo, 4);
	return (0);
}

void	ft_status(t_philo *philo)
{
	int	i;

	if ((philo->id + philo->round) % 2 == 1)
		i = 0;
	else
		i = 1;
	ft_status_p1(philo, i);
	if (!philo->is_dead)
		ft_status_p2(philo);
}
