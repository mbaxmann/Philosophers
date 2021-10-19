/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaxmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:34:56 by user42            #+#    #+#             */
/*   Updated: 2021/10/12 14:35:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->philo)
		{
			while (i < data->number)
			{
				pthread_mutex_destroy(&data->philo[i].left_fork);
				i++;
			}
			free(data->philo);
		}
		pthread_mutex_destroy(&data->write);
		free(data);
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		ft_putstr_fd("Error: Wrong number of argument\n", 2);
	else
	{
		data = ft_init(av, ac);
		if (!data)
			return (1);
		else
			ft_philo_start(data);
	}
	return (0);
}
