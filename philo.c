/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:38:49 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/20 20:52:34 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(unsigned int usec)
{
    long start_time;
    long ms;

    start_time = get_current_time();
    usleep(usec * 0.7);
    ms = usec/1000;
    while (get_current_time() - start_time < ms)
        usleep(100);
}

long	*start_time(void)
{
	static long	start_time;

	return (&start_time);
}

void	*start_routine(void *arg)
{
	t_philo	*philo_routine;

	philo_routine = (t_philo *)arg;
	if (philo_routine->shared_data->num_of_philo == 1)
	{
		single_philo(philo_routine);
		return NULL;
	}
	if (philo_routine->philo_id % 2 == 0)
		ft_usleep(50* 1000);
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
