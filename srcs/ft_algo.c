#include "../include/philosophers.h"

long long int    ft_gettime(void)
{
    struct timeval time;
    long long int first;

    gettimeofday(&time, NULL);
    first = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
    return (first);
}

long long int    ft_chrono(long long int last)
{
    return (ft_gettime() - last);
}

int     ft_is_dead(t_philo *philo)
{
    long long int time;
    static int dead = 0;

    pthread_mutex_lock(philo->write);
    time = ft_chrono(philo->time[1]);
    if (time > philo->time_to_die)
    {
        philo->is_dead = 1;
        if (!dead)
            printf("%lld %d is dead\n", ft_chrono(philo->time[0]), philo->id);
        if (!dead)
        {
            usleep(philo->time_to_die * 1000);
            dead = 1;
        }
        pthread_mutex_unlock(philo->write);
        return (1);
    }
    pthread_mutex_unlock(philo->write);
    return (0);
}

int     ft_act(int act, t_philo *philo)
{
    long long int i;
    long long int time;

    i = 0;
    if (act == 0)
        time = philo->time_to_eat;
    else
        time = philo->time_to_sleep;
    long long int time2;
    time2 = ft_gettime();
    while (ft_chrono(time2) < time)
    {
        usleep(1000);
        i++;
        if (ft_chrono(philo->time[1]) > philo->time_to_die)
        {
            return (1);
        }
    }
    return (0);
}

void    ft_is(t_philo *philo, int i)
{
    long long int time;

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

void    ft_status(t_philo *philo, int i)
{
    if (i == 0)
    {
        pthread_mutex_lock(&philo->left_fork);
        if (ft_is_dead(philo))
        {
            pthread_mutex_unlock(&philo->left_fork);
            return ;
        }
        ft_is(philo, 1);
        i++;
    }
    else if (i == 1)
    {
        pthread_mutex_lock(philo->right_fork);
        if (ft_is_dead(philo))
        {
            pthread_mutex_unlock(&philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
            return ;
        }
        ft_is(philo, 1);
        i++;
    }
    else if (i == 2)
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
}

void    *ft_routine(void *param)
{
    t_philo *philo;
    int i;
    int n;

    i = 0;
    n = -1;
    philo = (t_philo *)param;
    if (philo->id % 2 == 1)
        usleep(1000);
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

void    ft_philo_start(void *param)
{
    int i;
    t_data *data;
    pthread_t *th;

    i = 1;
    data = ((t_data *)param);
    th = (pthread_t *)malloc(sizeof(pthread_t) * (data->number));
    pthread_mutex_init(&data->lock, NULL);
    int k = 0;
    while (i < data->number)
    {
        k = pthread_create(th + i, NULL, &ft_routine, (void *)(data->philo + i));
        //printf("WARNING ERRO: %d\n", k);
        i += 2;
    }
    i = 0;
    while (i < data->number)
    {
        k = pthread_create(th + i, NULL, &ft_routine, (void *)(data->philo + i));
        //printf("WARNING ERRO: %d\n", k);
        i += 2;
    }
    i = 0;
    while (i < data->number)
    {
        //k = pthread_detach(th[i]);
        pthread_join(th[i], NULL);
        i++;
    }
    ft_free(data);
    free(th);
}

void    ft_algo(t_data *data)
{
    int         i;

    i = 0;
    data->current = 0;
    ft_philo_start(data);
}