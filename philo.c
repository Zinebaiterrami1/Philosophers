/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:38:49 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/08 19:54:46 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *start_routine(void *arg)
{
    s_philo *philo_routine;
    int i;

    philo_routine = (s_philo *)arg;
    i = 0;
    while(1)
    {
        printf("philo is thinkin\n");
        printf("philo is eating\n");
        usleep(5000);
        printf("philo is sleeping\n");
        i++;
        if(i == philo_routine->shared_data.num_of_philo)
        {
            printf("philo die\n");
            exit(0);
        }
    }
    //infinite loop
    //each philo will repeat this routine
    //think
    //eat
    //sleep
    //repeat until a philo dies
    //here i will use lock & unlock for forks
}

//init each philo with the followin data
//id
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
        philo[i].first = 0;
        philo[i].second = 0;
        if(av[5])
            philo[i].shared_data.num_of_meals = ft_atoi(av[5]);
        else
            philo[i].shared_data.num_of_meals = 0;
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

g_data *init_mutex(s_philo *philo_arr)
{
    g_data *mutex;
    int i;
    // int first;
    // int second;
    
    i = 0;
    mutex = malloc(sizeof(g_data) * philo_arr->shared_data.num_of_philo);
    pthread_mutex_init(&mutex, NULL);
    while(i < philo_arr->shared_data.num_of_philo)
    {
        if(philo_arr->philo_id % 2 == 0)
        {
            mutex[philo_arr->first].mutex_fork = philo_arr->philo_id;
            mutex[philo_arr->second].mutex_fork = (philo_arr->philo_id + 1) %  philo_arr->shared_data.num_of_philo;
            pthread_mutex_lock(&mutex[philo_arr->first]);
            pthread_mutex_lock(&mutex[philo_arr->second]);
        }
        else
        {
            mutex[philo_arr->first].mutex_fork = (philo_arr->philo_id + 1) %  philo_arr->shared_data.num_of_philo;
            mutex[philo_arr->second].mutex_fork = philo_arr->philo_id;
            pthread_mutex_lock(&mutex[philo_arr->first]);
            pthread_mutex_lock(&mutex[philo_arr->second]);
        }
        i++;
    }
    return (mutex);
}

int main(int ac, char **av)
{
    int num;
    g_data *mutex;
    s_philo *philo;
    int i;
    
    i = 0;
    if(!parse_args(av, ac))
        write(1, "invalid args!\n", 14);
    else
    {
        philo = init_philo(av);
        mutex = init_mutex(philo);
        while(i < philo->shared_data.num_of_philo)
        {
            pthread_mutex_unlock(&mutex[philo->first].mutex_fork);
            pthread_mutex_unlock(&mutex[philo->second].mutex_fork);
            i++;
        }
        pthread_mutex_destroy(&mutex);
    }
}

//num philo
//time to die
//time to eat
//time to sleep
//num of meals 