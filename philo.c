/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:38:49 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/20 16:17:57 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	*start_time(void)
{
	static long	start_time;

	return (&start_time);
}

void	*start_routine(void *arg)
{
	s_philo	*philo_routine;

	philo_routine = (s_philo *)arg;
	if (philo_routine->shared_data->num_of_philo == 1)
		single_philo(philo_routine);
	while (1)
		ft_philo_routine(philo_routine);
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

static void	helper_main(int num, s_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	forks = philo[0].shared_data->mutex_fork;
	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	int				num;
	s_philo			*philo;
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	if (!parse_args(av, ac))
	{
		write(1, "invalid args!\n", 14);
		return (1);
	}
	get_start_time();
	philo = init_philo(av);
	num = philo[0].shared_data->num_of_philo;
	ft_monitor(philo);
	helper_main(num, philo, forks);
	free(forks);
	free(philo);
}
