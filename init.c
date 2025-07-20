/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:06:13 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/20 16:25:08 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(int num)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * num);
	while (i < num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

static void	assign_forks(t_data *data, t_philo *philo, int i)
{
	while (i < data->num_of_philo)
	{
		philo[i].philo_id = i + 1;
		if (philo[i].philo_id % 2 == 0)
		{
			philo[i].first = i;
			philo[i].second = (i + 1) % data->num_of_philo;
		}
		else
		{
			philo[i].first = (i + 1) % data->num_of_philo;
			philo[i].second = i;
		}
		philo[i].last_meal = get_current_time();
		philo[i].shared_data = data;
		pthread_create(&philo[i].philo, NULL, start_routine, &philo[i]);
		i++;
	}
}

t_philo	*init_philo(char **av)
{
	t_philo	*philo;
	int		i;
	int		num;
	t_data	*data;

	num = ft_atoi(av[1]);
	i = 0;
	data = malloc(sizeof(t_data));
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->stop_simulation = 0;
	if (av[5])
		data->num_of_meals = ft_atoi(av[5]);
	else
		data->num_of_meals = -1;
	data->mutex_fork = init_forks(data->num_of_philo);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	philo = malloc(sizeof(t_philo) * data->num_of_philo);
	assign_forks(data, philo, i);
	return (philo);
}

void	print_philo(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->shared_data->stop_mutex);
	if (philo->shared_data->stop_simulation)
	{
		pthread_mutex_unlock(&philo->shared_data->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->shared_data->stop_mutex);
	pthread_mutex_lock(&philo->shared_data->mutex_print);
	printf("%ld %d %s\n", get_current_time(), philo->philo_id, msg);
	pthread_mutex_unlock(&philo->shared_data->mutex_print);
}
