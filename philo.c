/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:38:49 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/07 20:36:30 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void *start_routine(void *arg)
// {
//     //infinite loop
//     //each philo will repeat this routine
//     //think
//     //eat
//     //sleep
//     //repeat until a philo dies
//     //here i will use lock & unlock for forks
// }

s_philo *init_philo()
{
    
}

int main(int argc, char **argv)
{
    s_philo *philo;
    
    philo = malloc(sizeof(s_philo));
    if(!philo)
        return (-1);
    if(!parse_args(argv, argc))
        printf("invalid args!\n");
    else
        printf("continue...\n");
}