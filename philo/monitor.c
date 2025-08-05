/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:48:57 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/21 21:12:07 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mentor(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->shared_data->mutex_print);
	printf("%ld %d %s\n", get_current_time(), philo->philo_id, msg);
	pthread_mutex_unlock(&philo->shared_data->mutex_print);
}

static void	check_death(t_philo *philo, int i)
{
	pthread_mutex_unlock(&philo->shared_data->meal_mutex);
	stop_mutex(philo, i);
	print_mentor(&philo[i], "is died");
	return ;
}

static void	helper_monitor(int num, t_philo *philo)
{
	int (total_meals), (all_ate), (i);
	total_meals = philo->shared_data->num_of_meals;
	while (1)
	{
		all_ate = 1;
		i = 0;
		while (i < num)
		{
			pthread_mutex_lock(&philo->shared_data->meal_mutex);
			if (total_meals != -1 && get_meal_count(&philo[i]) < total_meals)
				all_ate = 0;
			if (get_current_time() - philo[i].last_meal
				> philo[i].shared_data->time_to_die)
			{
				check_death(philo, i);
			}
			pthread_mutex_unlock(&philo->shared_data->meal_mutex);
			i++;
		}
		if (total_meals != -1 && all_ate)
			return ;
		usleep(10);
	}
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		num;

	philo = (t_philo *)arg;
	num = philo->shared_data->num_of_philo;
	helper_monitor(num, philo);
	return (NULL);
}

void	ft_monitor(t_philo *philo)
{
	pthread_t	monitor_t;

	pthread_create(&monitor_t, NULL, monitor, philo);
	pthread_join(monitor_t, NULL);
}
