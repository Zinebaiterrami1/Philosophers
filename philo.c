/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:38:49 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/21 20:52:36 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_meal_count(t_philo *philo)
{
	int	c;

	pthread_mutex_lock(&philo->shared_data->count_mutex);
	c = philo->count_meals;
	pthread_mutex_unlock(&philo->shared_data->count_mutex);
	return (c);
}

void	inc_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared_data->count_mutex);
	philo->count_meals++;
	pthread_mutex_unlock(&philo->shared_data->count_mutex);
}

void	*check_meals(t_philo *philo_routine)
{
	if (philo_routine->shared_data->num_of_meals >= 0)
	{
		while (get_meal_count(philo_routine)
			< philo_routine->shared_data->num_of_meals)
		{
			if (ft_philo_routine(philo_routine))
				return (NULL);
			inc_meal_count(philo_routine);
		}
	}
	return (NULL);
}

void	*start_routine(void *arg)
{
	t_philo	*philo_routine;

	philo_routine = (t_philo *)arg;
	philo_routine->count_meals = 0;
	if (philo_routine->shared_data->num_of_philo == 1)
	{
		single_philo(philo_routine);
		return (NULL);
	}
	usleep(500);
	check_meals(philo_routine);
	while (1)
	{
		if (ft_philo_routine(philo_routine))
			return (NULL);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	int		i;
	int		num;

	i = 0;
	if (!parse_args(av, ac))
	{
		write(1, "invalid args!\n", 14);
		return (1);
	}
	get_start_time();
	philo = init_philo(av);
	ft_monitor(philo);
	num = philo[0].shared_data->num_of_philo;
	helper_main(philo, num);
	free(philo);
}
