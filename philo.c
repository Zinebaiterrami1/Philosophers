/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:38:49 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/11 19:40:59 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//start_routine
void *start_routine(void *arg)
{
    s_philo *philo_routine;

    philo_routine = (s_philo *)arg;
    while(1)
    {
        printf("Philo %d is thinking\n", philo_routine->philo_id);
        pthread_mutex_lock(&philo_routine->shared_data.mutex_fork[philo_routine->first]);;
        pthread_mutex_lock(&philo_routine->shared_data.mutex_fork[philo_routine->second]);
        
        printf("Philo %d is eating\n", philo_routine->philo_id);
        usleep(1000); //timetoeat * 1000
        pthread_mutex_unlock(&philo_routine->shared_data.mutex_fork[philo_routine->first]);
        pthread_mutex_unlock(&philo_routine->shared_data.mutex_fork[philo_routine->second]);
        
        printf("Philo %d is sleeping\n", philo_routine->philo_id);
        usleep(1000); //timesleep * 1000
    }
    return NULL;
}

//init_forks, make nbr forks shared between philosophers
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

//init_philo, create threads & initialize data
s_philo *init_philo(char **av)
{
    s_philo *philo;
    int i;
    int num;
    
    num = ft_atoi(av[1]);
    i = 0;
    philo = malloc(sizeof(s_philo) * num);
    while(i < num)
    {
        philo[i].philo_id = i;
        philo[i].shared_data.num_of_philo = num;
        philo[i].shared_data.time_to_die = ft_atoi(av[2]);
        philo[i].shared_data.time_to_eat = ft_atoi(av[3]);
        philo[i].shared_data.time_to_sleep = ft_atoi(av[4]);
        philo[i].shared_data.mutex_fork = init_forks(num);
        philo[i].first = i;
        philo[i].second = (i + 1) % num;
        if(av[5])
            philo[i].shared_data.num_of_meals = ft_atoi(av[5]);
        else
            philo[i].shared_data.num_of_meals = -1;
        pthread_create(&philo[i].philo, NULL, start_routine, &philo[i]);
        i++;
    }
    i = 0;
    while(i < num)
    {
        pthread_join(philo[i].philo, NULL);
        i++;
    }
    return (philo);
}

//main
int main(int ac, char **av)
{
    int num;
    s_philo *philo;
    pthread_mutex_t *forks;
    int i;
    
    i = 0;
    if(!parse_args(av, ac))
    {
        write(1, "invalid args!\n", 14);
        return (1);
    }
    philo = init_philo(av);
    forks = philo[0].shared_data.mutex_fork;
    num = philo[0].shared_data.num_of_philo;
    i = 0;
    while(i < num)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    free(forks);
    free(philo);
}