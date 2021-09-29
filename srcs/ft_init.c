#include "../include/philosophers.h"

int    ft_prep_philo(t_data *data, char **av)
{
    int i;

    i = 0;
    data->philo = (t_philo *)malloc(sizeof(t_philo) * data->number);
    if (!data->philo)
        return (1);
    while (i < data->number)
    {
        data->philo[i].id = i + 1;
        data->philo[i].is_eating = 0;
        data->philo[i].is_sleeping = 0;
        data->philo[i].is_thinking = 0;
        data->philo[i].is_alive = 1;
        data->philo[i].time_to_die = ft_atoi(av[2]);
        data->philo[i].time_to_eat = ft_atoi(av[3]);
        data->philo[i].time_to_sleep = ft_atoi(av[4]);
        i++;
    }
    return (0);
}

int     ft_check_value(t_data *data)
{
    if (data->number < 1 || data->philo[0].time_to_eat < 1
        || data->philo[0].time_to_die < 1 || data->philo[0].time_to_sleep < 1)
        return (0);
    return (1);
}

int    ft_prep_forks(t_data *data)
{
    data->forks = (int *)malloc(sizeof(int) * (data->number + 1));
    if (!data->forks)
    {
        free(data->philo);
        return (1);
    }
    memset(data->forks, 0, sizeof(int) * (data->number + 1));
    return (0);
}

t_data *ft_init(char **av)
{
    t_data *data;
    int     err;

    err = 0;
    data = (t_data *)malloc(sizeof(t_data));
    data->number = ft_atoi(av[1]);
    err += ft_prep_philo(data, av);
    err += ft_prep_forks(data);
    if (err)
    {
        free(data);
        ft_putstr_fd("Error: Malloc failed\n", 2);
        data = NULL;
    }
    if (!ft_check_value(data))
    {
        free(data);
        ft_putstr_fd("Error: Invalid arguments\n", 2);
        return (NULL);
    }
    return (data);
}