/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:38:49 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/21 14:33:46 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(int ms)
{
    long start_time;

    start_time = get_current_time();
    while (get_current_time() - start_time < ms) 
        usleep(100);
}

long	*start_time(void)
{
	static long	start_time;

	return (&start_time);
}
int	get_meal_count(t_philo *philo)
{
	int c; 
	pthread_mutex_lock(&philo->shared_data->count_mutex);
		c = philo->count_meals;
	pthread_mutex_unlock(&philo->shared_data->count_mutex);
	return(c);
}

void	inc_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared_data->count_mutex);
		philo->count_meals ++;
	pthread_mutex_unlock(&philo->shared_data->count_mutex);
}

void	*start_routine(void *arg)
{
	t_philo	*philo_routine;
	
	philo_routine = (t_philo *)arg;
	philo_routine->count_meals = 0;
	if (philo_routine->shared_data->num_of_philo == 1)
	{
		single_philo(philo_routine);
		return NULL;
	}
	usleep(500);
	
	if(philo_routine->shared_data->num_of_meals >= 0)
	{
		while(philo_routine->count_meals < philo_routine->shared_data->num_of_meals)
		{
			if(ft_philo_routine(philo_routine))
				return (NULL);	
			inc_meal_count(philo_routine);
		}
	}
	return(NULL);
	while (1)
	{
		if(ft_philo_routine(philo_routine))
			return (NULL);
	}
	return (NULL);
}

void	get_start_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("error in time\n");
		exit(EXIT_FAILURE);
	}
	*start_time() = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

long	get_current_time(void)
{
	struct timeval	tv;
	long			current_time;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("error in time\n");
		exit(EXIT_FAILURE);
	}
	current_time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - *start_time();
	return (current_time);
}

static void	helper_main(t_philo *philo,int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&philo[i].shared_data->mutex_fork[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	int				i;
	int num;
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
	helper_main( philo,num);
	free(philo);
}
