#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct      s_philo
{
    int id;
    int is_sleeping;
    int is_eating;
    int is_thinking;
    int is_alive;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
}                   t_philo;

typedef struct      s_data
{
    int number;
    int current;
    int *forks;
    struct timeval time_begin;
    t_philo *philo;
    pthread_mutex_t lock;
}                   t_data;

t_data  *ft_init(char **av);
void    ft_putstr_fd(char *s, int fd);
void    ft_algo(t_data *data);
void    *ft_routine(void *param);
int     ft_prep_philo(t_data *data, char **av);
int     ft_prep_forks(t_data *data);
int     ft_atoi(const char *str);
int     ft_isminus(char c, int *i);
int     ft_check_value(t_data *data);

#endif