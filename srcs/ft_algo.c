#include "../include/philosophers.h"

void    *ft_routine(void *param)
{
    struct timeval  time[2];
    t_philo     philo;

    pthread_mutex_lock(&((t_data *)param)->lock);
    time[0].tv_usec = ((t_data *)param)->time_begin.tv_usec;
    philo = ((t_data *)param)->philo[((t_data *)param)->current];
    ((t_data *)param)->current++;
    pthread_mutex_unlock(&((t_data *)param)->lock);
    while (philo.is_alive)
    {
        gettimeofday(&time[1], NULL);
        time[1].tv_usec -= time[0].tv_usec;
        printf("Philo%d: I am alive !!! and the time is : %ld\n", philo.id, time[1].tv_usec);
        usleep(300);
        philo.is_alive = 0;
        gettimeofday(&time[1], NULL);
        time[1].tv_usec -= time[0].tv_usec;
        printf("Philo%d: I am dead :( and the time is : %ld\n", philo.id, time[1].tv_usec);
    }
    return (NULL);
}

void    ft_algo(t_data *data)
{
    pthread_t   *th;
    int         i;

    i = 0;
    data->current = 0;
    gettimeofday(&data->time_begin, NULL);
    th = (pthread_t *)malloc(sizeof(pthread_t) * data->number);
    pthread_mutex_init(&data->lock, NULL);
    while (i < data->number)
    {
        pthread_create(th + i, NULL, &ft_routine, (void *)data);
        i++;
    }
    i = 0;
    while (i < data->number)
    {
        pthread_join(th[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&data->lock);
}