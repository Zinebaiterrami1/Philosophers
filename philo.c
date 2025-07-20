/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:38:49 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/20 14:45:38 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//start_routine
long *start_time(void)
{
    static long start_time;
    return (&start_time);
}


// static void assign_forks(s_philo *philo)
// {
//     int philo_nbr;
//     int i;

//     philo_nbr = philo->shared_data->num_of_philo;
//     i = 0;
//     while (i < philo_nbr)
//     {
//         if (philo->philo_id % 2 == 0)
//         {
//             philo->first = i;
//             if (philo->philo_id == philo_nbr)
//                 philo->second = 0;
//             else
//                 philo->second = philo->philo_id;
//         }
//         else
//         {
//             philo->second = i;
//             if (philo->philo_id == philo_nbr)
//                 philo->first = 0;
//             else
//                 philo->first = philo->philo_id;
//         }
//         i++;
//     }
// }

void *start_routine(void *arg)
{
    s_philo *philo_routine;
    
    philo_routine = (s_philo *)arg;
    
    if(philo_routine->shared_data->num_of_philo == 1)
    {
        print_philo(philo_routine, "is thinking");
        pthread_mutex_lock(&philo_routine->shared_data->mutex_fork[philo_routine->first]);
        print_philo(philo_routine, "has taken a fork");
        // usleep(philo_routine->shared_data->time_to_die * 1000);
        pthread_mutex_lock(&philo_routine->shared_data->stop_mutex);
        if(philo_routine->shared_data->stop_simulation == 1)
        {
            pthread_mutex_unlock(&philo_routine->shared_data->mutex_fork[philo_routine->first]);
            // printf("%ld %d %s", get_current_time(), philo_routine->philo_id, "is died\n");
            pthread_mutex_unlock(&philo_routine->shared_data->stop_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&philo_routine->shared_data->stop_mutex);
        pthread_mutex_unlock(&philo_routine->shared_data->mutex_fork[philo_routine->first]);
        // printf("%ld %d %s", get_current_time(), philo_routine->philo_id, "is died\n");
        return NULL;
    }
    while(1)
    {
        usleep(1000);
        pthread_mutex_lock(&philo_routine->shared_data->stop_mutex);
        if(philo_routine->shared_data->stop_simulation)
        {
            pthread_mutex_unlock(&philo_routine->shared_data->stop_mutex);
            // printf("dead");
            return (NULL);
        }
        pthread_mutex_unlock(&philo_routine->shared_data->stop_mutex);

        print_philo(philo_routine, "is thinking");
        if (philo_routine->philo_id % 2) //odd
            usleep(200);
        pthread_mutex_lock(&philo_routine->shared_data->mutex_fork[philo_routine->first]);
        print_philo(philo_routine, "has taken a fork");
        pthread_mutex_lock(&philo_routine->shared_data->mutex_fork[philo_routine->second]);
        print_philo(philo_routine, "has taken a fork");
        // } else {
        //     pthread_mutex_lock(&philo_routine->shared_data->mutex_fork[philo_routine->second]);
        //     print_philo(philo_routine, "has taken a fork");
        //     pthread_mutex_lock(&philo_routine->shared_data->mutex_fork[philo_routine->first]);
        //     print_philo(philo_routine, "has taken a fork");
        // }

        pthread_mutex_lock(&philo_routine->shared_data->meal_mutex);
        philo_routine->last_meal = get_current_time();
        pthread_mutex_unlock(&philo_routine->shared_data->meal_mutex);
        print_philo(philo_routine, "is eating");

        usleep(philo_routine->shared_data->time_to_eat * 1000);
        
        pthread_mutex_unlock(&philo_routine->shared_data->mutex_fork[philo_routine->first]);
        pthread_mutex_unlock(&philo_routine->shared_data->mutex_fork[philo_routine->second]);

        print_philo(philo_routine, "is sleeping");
        usleep(philo_routine->shared_data->time_to_sleep * 1000);
    }
    return (NULL);
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

void print_philo(s_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->shared_data->stop_mutex);
    if (philo->shared_data->stop_simulation) {
        pthread_mutex_unlock(&philo->shared_data->stop_mutex);
        return;
    }
    pthread_mutex_unlock(&philo->shared_data->stop_mutex);
    pthread_mutex_lock(&philo->shared_data->mutex_print);
    printf("%ld %d %s\n", get_current_time(),philo->philo_id, msg);
    pthread_mutex_unlock(&philo->shared_data->mutex_print);
}

void get_start_time(void)
{
    struct timeval tv;
    
    if(gettimeofday(&tv, NULL) == -1)
    {
        printf("error in time\n");
        exit(EXIT_FAILURE);
    }
    *start_time() = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    // printf(" start time ============> %ld\n" ,*start_time());

    // return ((tv->tv_sec * 1000) + (tv->tv_usec / 1000));
    //get time of day
    //convert it to miliseconds
    //return start time of program
}

long get_current_time(void)
{
    struct timeval tv;

    if(gettimeofday(&tv, NULL) == -1)
    {
        printf("error in time\n");
        exit(EXIT_FAILURE);
    }
    long current_time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000))- *start_time();
    // printf("current time ==========>%ld start time ============> %ld\n", current_time, *start_time());
    return (current_time);
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
    get_start_time();
    philo = init_philo(av);
    num = philo[0].shared_data->num_of_philo;
    ft_monitor(philo);
    i = 0;
    while(i < num)
    {
        pthread_join(philo[i].philo, NULL);
        i++;
    }
    forks = philo[0].shared_data->mutex_fork;
    i = 0;
    while(i < num)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    free(forks);
    free(philo);
}