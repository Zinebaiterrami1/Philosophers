/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:06:13 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/20 15:08:59 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t *init_forks(int num)
{
    pthread_mutex_t *forks;
    int i;

    i = 0;
    forks = malloc(sizeof(pthread_mutex_t) * num);
    while(i < num)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    return (forks);
}

static void assign_forks(s_philo *philo, )
{

}

s_philo *init_philo(char **av)
{
    s_philo *philo;
    int i;
    int num;
    g_data *data;
    
    num = ft_atoi(av[1]);
    i = 0;
    data = malloc(sizeof(g_data));
    data->num_of_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->stop_simulation = 0;
    if(av[5])
        data->num_of_meals = ft_atoi(av[5]);
    else
        data->num_of_meals = -1;
    data->mutex_fork = init_forks(data->num_of_philo);
    pthread_mutex_init(&data->meal_mutex, NULL);
    pthread_mutex_init(&data->stop_mutex, NULL);
    pthread_mutex_init(&data->mutex_print, NULL);
    philo = malloc(sizeof(s_philo) * data->num_of_philo);
    while(i < data->num_of_philo)
    {
        philo[i].philo_id = i + 1;
        if(philo[i].philo_id % 2 == 0) //eeven
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
    return (philo);
}
