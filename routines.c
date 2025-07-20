/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:20:28 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/20 16:37:27 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_philo(t_philo *philo_routine)
{
	print_philo(philo_routine, "is thinking");
	pthread_mutex_lock(
            &philo_routine->shared_data->mutex_fork[philo_routine->first]);
	print_philo(philo_routine, "has taken a fork");
	pthread_mutex_lock(&philo_routine->shared_data->stop_mutex);
	if (philo_routine->shared_data->stop_simulation == 1)
	{
		pthread_mutex_unlock(&philo_routine->shared_data->mutex_fork[philo_routine->first]);
		pthread_mutex_unlock(&philo_routine->shared_data->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo_routine->shared_data->stop_mutex);
	pthread_mutex_unlock(&philo_routine->shared_data->mutex_fork[philo_routine->first]);
	return ;
}

void	stop_simulation(t_philo *philo_routine)
{
	pthread_mutex_lock(&philo_routine->shared_data->stop_mutex);
	if (philo_routine->shared_data->stop_simulation)
	{
		pthread_mutex_unlock(&philo_routine->shared_data->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo_routine->shared_data->stop_mutex);
}

void	ft_philo_routine(t_philo *philo_routine)
{
	usleep(1000);
	stop_simulation(philo_routine);
	print_philo(philo_routine, "is thinking");
	if (philo_routine->philo_id % 2)
		usleep(200);
	pthread_mutex_lock(&philo_routine->shared_data->mutex_fork[philo_routine->first]);
	print_philo(philo_routine, "has taken a fork");
	pthread_mutex_lock(&philo_routine->shared_data->mutex_fork[philo_routine->second]);
	print_philo(philo_routine, "has taken a fork");
	pthread_mutex_lock(&philo_routine->shared_data->meal_mutex);
	philo_routine->last_meal = get_current_time();
	pthread_mutex_unlock(&philo_routine->shared_data->meal_mutex);
	print_philo(philo_routine, "is eating");
	usleep(philo_routine->shared_data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo_routine->shared_data->mutex_fork[philo_routine->first]);
	pthread_mutex_unlock(&philo_routine->shared_data->mutex_fork[philo_routine->second]);
	print_philo(philo_routine, "is sleeping");
	usleep(philo_routine->shared_data->time_to_sleep * 1000);
}
