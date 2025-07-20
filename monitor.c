/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:48:57 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/20 16:40:31 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mentor(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->shared_data->mutex_print);
	printf("%ld %d %s\n", get_current_time(), philo->philo_id, msg);
	pthread_mutex_unlock(&philo->shared_data->mutex_print);
}

static void	helper_monitor(int num, t_philo *philo)
{
	long	meal;
	int		i;

	while (1)
	{
		i = 0;
		while (i < num)
		{
			pthread_mutex_lock(&philo->shared_data->meal_mutex);
			meal = get_current_time() - philo[i].last_meal;
			pthread_mutex_unlock(&philo->shared_data->meal_mutex);
			if (meal > philo[i].shared_data->time_to_die)
			{
				pthread_mutex_lock(&philo[i].shared_data->stop_mutex);
				philo[i].shared_data->stop_simulation = 1;
				pthread_mutex_unlock(&philo[i].shared_data->stop_mutex);
				print_mentor(&philo[i], "is died");
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		num;
	int		i;
	long	meal;

	i = 0;
	philo = (t_philo *)arg;
	num = philo->shared_data->num_of_philo;
	helper_monitor(num, philo);
}

void	ft_monitor(t_philo *philo)
{
	pthread_t	monitor_t;

	pthread_create(&monitor_t, NULL, monitor, philo);
	pthread_join(monitor_t, NULL);
}
