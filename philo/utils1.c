/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:56:24 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/21 20:52:55 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int ms)
{
	long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < ms)
		usleep(100);
}

long	*start_time(void)
{
	static long	start_time;

	return (&start_time);
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

void	helper_main(t_philo *philo, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
}
