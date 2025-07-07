/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:38:46 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/07 17:39:35 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <threads.h>
#include <stdio.h>
#include <pthread.h>

typedef struct t_data
{
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_of_philo;
    int num_of_meals; //max_eat_time
} g_data;

typedef struct t_philo
{

    pthread_t philo;
    int             philo_id;
    g_data shared_data;
} s_philo;

int	ft_atoi(const char *str);
int	ft_is_numeric(char *str);
int parse_args(char **argv, int argc);

#endif