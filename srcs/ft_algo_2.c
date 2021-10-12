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
	long long int	time;

	time = ft_gettime() - philo->time[0];
	pthread_mutex_lock(philo->write);
	if (i == 1)
		printf("%lld %d has taken a fork\n", time, philo->id);
	else if (i == 2)
		printf("%lld %d is eating\n", time, philo->id);
	else if (i == 3)
		printf("%lld %d is sleeping\n", time, philo->id);
	else if (i == 4)
		printf("%lld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(philo->write);
}

int	ft_status_p1(t_philo *philo, int i)
{
	if (i == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		if (ft_is_dead(philo))
		{
			pthread_mutex_unlock(&philo->left_fork);
			return (1);
		}
		ft_is(philo, 1);
	}
	return (0);
}

int	ft_status_p2(t_philo *philo, int i)
{
	if (i == 1)
	{
		if (!philo->right_fork)
		{
			ft_usleep(philo->time_to_die * 1000);
			pthread_mutex_unlock(&philo->left_fork);
			return (1);
		}
		pthread_mutex_lock(philo->right_fork);
		if (ft_is_dead(philo))
		{
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
		ft_is(philo, 1);
	}
	return (0);
}

int	ft_status_p3(t_philo *philo, int i)
{
	if (i == 2)
	{
		ft_is(philo, 2);
		philo->time[1] = ft_gettime();
		ft_act(0, philo);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		i++;
	}
	else if (i == 3)
	{
		ft_is(philo, 3);
		ft_act(1, philo);
		i++;
	}
	else if (i == 4)
	{
		if (philo->hungry)
			philo->hungry--;
		ft_is(philo, 4);
		i = 0;
	}
	return (0);
}

void	ft_status(t_philo *philo, int i)
{
	int	ret;

	ret = 0;
	ret += ft_status_p1(philo, i);
	if (ret)
		return ;
	ret += ft_status_p2(philo, i);
	if (ret)
		return ;
	ft_status_p3(philo, i);
}
