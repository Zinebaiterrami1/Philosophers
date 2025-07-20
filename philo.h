/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:38:46 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/20 16:40:31 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <threads.h>
# include <unistd.h>

typedef struct s_data
{
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	stop_mutex;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_philo;
	int				num_of_meals;
	int				stop_simulation;
}					t_data;

typedef struct t_philo
{
	pthread_t		philo;
	int				philo_id;
	int				first;
	int				second;
	long			last_meal;
	t_data			*shared_data;
}					t_philo;

int					ft_atoi(const char *str);
int					ft_is_numeric(char *str);
int					parse_args(char **argv, int argc);
void				print_philo(t_philo *philo, char *msg);
long				get_current_time(void);
void				get_start_time(void);
long				*start_time(void);
void				ft_monitor(t_philo *philo);
void				*monitor(void *arg);
void				*start_routine(void *arg);
pthread_mutex_t		*init_forks(int num);
t_philo				*init_philo(char **av);
void				print_philo(t_philo *philo, char *msg);
void				single_philo(t_philo *philo_routine);
void				stop_simulation(t_philo *philo_routine);
void				ft_philo_routine(t_philo *philo_routine);
#endif