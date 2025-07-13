/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:48:57 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/13 17:14:12 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *arg)
{
    s_philo *philo;
    int num;
    int i;

    i = 0;
    philo = (s_philo *)arg;
    num = philo->shared_data.num_of_philo;
    while(1)
    {
        while(i < num)
        {
            if(get_current_time() - philo[i].last_meal > philo[i].shared_data.time_to_die)
            {
                print_philo(&philo[i], "is died");
                exit (0);
            }
            i++;
        }
        usleep(1000); // sleep 1ms to avoid busy loop
    }
}

void ft_monitor(s_philo *philo)
{
    pthread_t monitor_t;
    
    pthread_create(&monitor_t, NULL, monitor, philo);
    pthread_join(monitor_t, NULL);
}