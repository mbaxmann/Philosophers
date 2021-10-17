/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaxmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:34:40 by user42            #+#    #+#             */
/*   Updated: 2021/10/12 14:56:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_prep_philo_2(t_data *data, char **av, int i)
{
	data->philo[i].time[0] = ft_gettime();
	data->philo[i].time[1] = ft_gettime();
	data->philo[i].time_to_die = ft_atoi(av[2]);
	data->philo[i].time_to_eat = ft_atoi(av[3]);
	data->philo[i].time_to_sleep = ft_atoi(av[4]);
	data->philo[i].write = &data->write;
	data->philo[i].right_fork = NULL;
	pthread_mutex_init(&data->philo[i].lock, NULL);
}

int	ft_prep_philo(t_data *data, char **av, int ac)
{
	int	i;

	i = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->number);
	if (!data->philo)
		return (1);
	while (i < data->number)
	{
		data->philo[i].id = i + 1;
		data->philo[i].hungry = 0;
		if (ac == 6)
			data->philo[i].hungry = ft_atoi(av[5]);
		data->philo[i].is_dead = 0;
		data->philo[i].round = 0;
		ft_prep_philo_2(data, av, i);
		i++;
	}
	return (0);
}

int	ft_check_value(t_data *data, char **av, int ac)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (i < ac)
	{
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0')
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	if (data->number < 1 || data->philo[0].time_to_eat < 1
		|| data->philo[0].time_to_die < 1 || data->philo[0].time_to_sleep < 1)
		return (0);
	return (1);
}

int	ft_prep_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		i++;
	}
	i = 0;
	while (i < data->number)
	{
		if (i == data->number - 1 && data->number > 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else if (data->number > 1)
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		i++;
	}
	return (0);
}

t_data	*ft_init(char **av, int ac)
{
	t_data	*data;
	int		err;

	data = NULL;
	err = 0;
	data = (t_data *)malloc(sizeof(t_data));
	data->philo = NULL;
	data->number = ft_atoi(av[1]);
	pthread_mutex_init(&(data->write), NULL);
	pthread_mutex_init(&data->lock, NULL);
	err += ft_prep_philo(data, av, ac);
	err += ft_prep_forks(data);
	if (err)
	{
		ft_free(data);
		ft_putstr_fd("Error: Malloc failed\n", 2);
		data = NULL;
	}
	if (!ft_check_value(data, av, ac))
	{
		ft_free(data);
		ft_putstr_fd("Error: Invalid arguments\n", 2);
		return (NULL);
	}
	return (data);
}
