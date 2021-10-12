/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaxmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:35:38 by user42            #+#    #+#             */
/*   Updated: 2021/10/12 14:35:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				is_dead;
	int				is_last;
	int				hungry;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long int	time[2];
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write;
}				t_philo;

typedef struct s_data
{
	int				number;
	int				current;
	struct timeval	time_begin;
	t_philo			*philo;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
}				t_data;

t_data			*ft_init(char **av, int ac);
void			ft_putstr_fd(char *s, int fd);
void			ft_algo(t_data *data);
void			*ft_routine(void *param);
void			ft_free(t_data *data);
void			ft_is(t_philo *philo, int i);
void			ft_usleep(int time);
void			ft_status(t_philo *philo, int i);
void			ft_free(t_data *data);
void			ft_philo_start(void *param);
void			ft_prep_philo_2(t_data *data, char **av, int i);
int				main(int ac, char **av);
int				ft_status_p1(t_philo *philo, int i);
int				ft_status_p2(t_philo *philo, int i);
int				ft_status_p3(t_philo *philo, int i);
int				ft_prep_philo(t_data *data, char **av, int ac);
int				ft_prep_forks(t_data *data);
int				ft_atoi(const char *str);
int				ft_isminus(char c, int *i);
int				ft_check_value(t_data *data, char **av, int ac);
int				ft_is_dead(t_philo *philo);
int				ft_act(int act, t_philo *philo);
long long int	ft_gettime(void);
long long int	ft_chrono(long long int last);

#endif
