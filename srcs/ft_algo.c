#include "../include/philosophers.h"

long int    ft_gettime(void)
{
    struct timeval time;
    long int first;

    gettimeofday(&time, NULL);
    first = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
    return (first);
}

long int    ft_chrono(long int last)
{
    return (ft_gettime() - last);
}

void    *ft_check_death(void *param)
{
    int i;
    static long int time_begin = 0;
    t_data *data;

    pthread_mutex_lock(&((t_data *)param)->lock);
    data = ((t_data *)param);
    pthread_mutex_unlock(&((t_data *)param)->lock);
    i = 0;
    time_begin = ft_gettime();
    while (1)
    {
        while (i < data->number)
        {
            write(1, "A", 1);
            pthread_mutex_lock(&data->philo[i].meal);
            if (ft_chrono(data->philo[i].last_meal) > data->philo[i].time_to_die)
            {
                pthread_mutex_lock(&data->lock);
                data->death = 1;
                pthread_mutex_unlock(&data->lock);
                printf("%ld %d is dead\n", ft_chrono(time_begin), i + 1);
                return (NULL);
            }
            pthread_mutex_unlock(&data->philo[i].meal);
            i++;
        }
        i = 0;
    }
    return (NULL);
}

int     ft_is_dead(t_data *data)
{
    int ret;

    pthread_mutex_lock(&data->lock);
    ret = data->death;
    pthread_mutex_unlock(&data->lock);
    return (ret);
}

void    *ft_routine(void *param)
{
    t_philo     philo;
    int         current;
    long int    time_begin;

    pthread_mutex_lock(&((t_data *)param)->lock);
    current = ((t_data *)param)->current;
    philo = ((t_data *)param)->philo[current];
    ((t_data *)param)->current++;
    pthread_mutex_unlock(&((t_data *)param)->lock);
    time_begin = ft_gettime();
    while (1)
    {
        pthread_mutex_lock(&philo.left_fork);
        if (ft_is_dead(param))
            return (NULL);
        printf("%ld %d has taken a fork\n", ft_chrono(time_begin), philo.id);
        pthread_mutex_lock(philo.right_fork);
        if (ft_is_dead(param))
            return (NULL);
        printf("%ld %d has taken a fork\n", ft_chrono(time_begin), philo.id);
        pthread_mutex_lock(&philo.meal);
        philo.last_meal = ft_gettime();
        pthread_mutex_unlock(&philo.meal);
        if (ft_is_dead(param))
            return (NULL);
        printf("%ld %d is eating\n", ft_chrono(time_begin), philo.id);
        usleep(philo.time_to_eat * 1000);
        pthread_mutex_lock(&philo.meal);
        philo.last_meal = ft_gettime();
        pthread_mutex_unlock(&philo.meal);
        pthread_mutex_unlock(&philo.left_fork);
        pthread_mutex_unlock(philo.right_fork);
        if (ft_is_dead(param))
            return (NULL);
        printf("%ld %d is sleeping\n", ft_chrono(time_begin), philo.id);
        usleep(philo.time_to_sleep * 1000);
        if (ft_is_dead(param))
            return (NULL);
        printf("%ld %d is thinking\n", ft_chrono(time_begin), philo.id);
    }
    return (NULL);
}

void    ft_philo_start(void *param)
{
    int i;
    t_data *data;
    pthread_t *th;

    i = 0;
    data = ((t_data *)param);
    th = (pthread_t *)malloc(sizeof(pthread_t) * (data->number + 1));
    pthread_mutex_init(&data->lock, NULL);
    pthread_create(th + (data->number), NULL, &ft_check_death, (void *)data);
    pthread_detach(th[data->number]);
    while (i < data->number)
    {
        pthread_create(th + i, NULL, &ft_routine, (void *)data);
        //pthread_detach(th[i]);
        i += 2;
    }
    i = 1;
    while (i < data->number)
    {
        pthread_create(th + i, NULL, &ft_routine, (void *)data);
        //pthread_detach(th[i]);
        i += 2;
    }
    i = 0;
    while (i < data->number)
        pthread_join(th[i++], NULL);
}

void    ft_algo(t_data *data)
{
    int         i;

    i = 0;
    data->current = 0;
    ft_philo_start(data);
}