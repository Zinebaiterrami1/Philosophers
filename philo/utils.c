/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:06:59 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/21 21:11:43 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	result;
	int			sign;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = sign * -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

int	parse_args(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i < argc)
	{
		if (!ft_is_numeric(argv[i]) || ft_atoi(argv[i]) <= 0
			|| ft_atoi(argv[i]) > INT_MAX)
			return (0);
		i++;
	}
	if ((ft_atoi(argv[1]) > 200 && ft_atoi(argv[1]) == 0)
		|| ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60
		|| ft_atoi(argv[4]) < 60)
		return (0);
	if (argc == 6)
	{
		if (!ft_is_numeric(argv[5]) || (ft_atoi(argv[5]) <= 0
				&& ft_atoi(argv[5]) > INT_MAX))
			return (0);
	}
	return (1);
}

void	stop_mutex(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo[i].shared_data->stop_mutex);
	philo[i].shared_data->stop_simulation = 1;
	pthread_mutex_unlock(&philo[i].shared_data->stop_mutex);
}
