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

int     ft_is_dead(long int last_meal, t_philo *philo, long int time_begin)
{
    long int time;
    static int dead = 0;

    pthread_mutex_lock(philo->write);
    time = ft_chrono(last_meal);
    if (time > philo->time_to_die)
    {
        philo->is_dead = 1;
        if (!dead)
        {
            printf("%ld %d is dead\n", ft_chrono(time_begin), philo->id);
            dead = 1;
        }
        usleep(philo->time_to_die * 1000 + 1);
        pthread_mutex_unlock(philo->write);
        return (1);
    }
    pthread_mutex_unlock(philo->write);
    return (0);
}

int     ft_act(int act, long int last_meal, t_philo *philo)
{
    int i;
    int time;

    i = 0;
    if (act == 0)
        time = philo->time_to_eat;
    else
        time = philo->time_to_sleep;
    while (i < time)
    {
        usleep(1000);
        i++;
        if (ft_chrono(last_meal) > philo->time_to_die)
            return (1);
    }
    return (0);
}

void    *ft_routine(void *param)
{
    t_philo     *philo;
    long int    time_begin;
    long int    last_meal;

    philo = (t_philo *)param;
    if (philo->id % 2 == 0)
        usleep(philo->time_to_eat / 10);
    time_begin = ft_gettime();
    last_meal = time_begin;
    while (!philo->is_dead)
    {
        if (ft_is_dead(last_meal, philo, time_begin))
            return (NULL);
        pthread_mutex_lock(&philo->left_fork);
        if (ft_is_dead(last_meal, philo, time_begin))
            return (NULL);
        pthread_mutex_lock(philo->write);
        printf("%ld %d has taken a fork\n", ft_chrono(time_begin), philo->id);
        pthread_mutex_unlock(philo->write);
        if (ft_is_dead(last_meal, philo, time_begin))
        {
            pthread_mutex_unlock(&philo->left_fork);
            return (NULL);
        }
        pthread_mutex_lock(philo->right_fork);
        if (ft_is_dead(last_meal, philo, time_begin))
        {
            pthread_mutex_unlock(&philo->left_fork);
            return (NULL);
        }
        pthread_mutex_lock(philo->write);
        printf("%ld %d has taken a fork\n", ft_chrono(time_begin), philo->id);
        pthread_mutex_unlock(philo->write);
        if (ft_is_dead(last_meal, philo, time_begin))
        {
            pthread_mutex_unlock(&philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
            return (NULL);
        }
        pthread_mutex_lock(philo->write);
        printf("%ld %d is eating\n", ft_chrono(time_begin), philo->id);
        pthread_mutex_unlock(philo->write);
        ft_act(0, last_meal, philo);
        last_meal = ft_gettime();
        pthread_mutex_unlock(&philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        if (ft_is_dead(last_meal, philo, time_begin))
            return (NULL);
        pthread_mutex_lock(philo->write);
        printf("%ld %d is sleeping\n", ft_chrono(time_begin), philo->id);
        pthread_mutex_unlock(philo->write);
        ft_act(1, last_meal, philo);
        if (ft_is_dead(last_meal, philo, time_begin))
            return (NULL);
        pthread_mutex_lock(philo->write);
        printf("%ld %d is thinking\n", ft_chrono(time_begin), philo->id);
        pthread_mutex_unlock(philo->write);
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
    th = (pthread_t *)malloc(sizeof(pthread_t) * (data->number));
    pthread_mutex_init(&data->lock, NULL);
    while (i < data->number)
    {
        pthread_create(th + i, NULL, &ft_routine, (void *)(data->philo + i));
        //pthread_detach(th[i]);
        i++;
    }
    i = 0;
    while (i < data->number)
    {
        //k = pthread_detach(th[i]);
        pthread_join(th[i], NULL);
        i++;
    }
}

void    ft_algo(t_data *data)
{
    int         i;

    i = 0;
    data->current = 0;
    ft_philo_start(data);
}