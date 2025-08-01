/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:20:28 by zait-err          #+#    #+#             */
/*   Updated: 2025/08/01 09:34:11 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_philo(t_philo *philo_routine)
{
	print_philo(philo_routine, "is thinking");
	pthread_mutex_lock(&philo_routine
		->shared_data
		->mutex_fork[philo_routine->first]);
	print_philo(philo_routine, "has taken a fork");
	pthread_mutex_unlock(&philo_routine
		->shared_data
		->mutex_fork[philo_routine->first]);
	return ;
}

int	stop_simulation(t_philo *philo_routine)
{
	pthread_mutex_lock(&philo_routine->shared_data->stop_mutex);
	if (philo_routine->shared_data->stop_simulation)
	{
		pthread_mutex_unlock(&philo_routine->shared_data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo_routine->shared_data->stop_mutex);
	return (0);
}

static void	lock_forks(t_philo *philo_routine)
{
	pthread_mutex_lock(&philo_routine
		->shared_data
		->mutex_fork[philo_routine->first]);
	print_philo(philo_routine, "has taken a fork");
	pthread_mutex_lock(&philo_routine
		->shared_data
		->mutex_fork[philo_routine->second]);
	print_philo(philo_routine, "has taken a fork");
}

int	ft_philo_routine(t_philo *philo_routine)
{
	usleep(500);
	if (stop_simulation(philo_routine))
		return (1);
	print_philo(philo_routine, "is thinking");
	if (philo_routine->philo_id % 2 == 0)
		usleep(200);
	lock_forks(philo_routine);
	pthread_mutex_lock(&philo_routine->shared_data->meal_mutex);
	philo_routine->last_meal = get_current_time();
	pthread_mutex_unlock(&philo_routine->shared_data->meal_mutex);
	print_philo(philo_routine, "is eating");
	ft_usleep(philo_routine->shared_data->time_to_eat);
	pthread_mutex_unlock(&philo_routine
		->shared_data
		->mutex_fork[philo_routine->first]);
	pthread_mutex_unlock(&philo_routine
		->shared_data
		->mutex_fork[philo_routine->second]);
	print_philo(philo_routine, "is sleeping");
	ft_usleep(philo_routine->shared_data->time_to_sleep);
	return (0);
}

void	destroy_mutex(t_philo *philo)
{
	pthread_mutex_destroy(&philo->shared_data->meal_mutex);
	pthread_mutex_destroy(&philo->shared_data->stop_mutex);
	pthread_mutex_destroy(&philo->shared_data->mutex_print);
	pthread_mutex_destroy(&philo->shared_data->count_mutex);
	free(philo->shared_data->mutex_fork);
	free(philo->shared_data);
}
