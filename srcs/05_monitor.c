/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:12:00 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/13 14:46:38 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

// monitor thread routine
void    *ft_monitor_routine(void *pointer)
{
    t_data  *data;

    data = (t_data *)pointer;
    pthread_mutex_lock(&data->write_lock);
    ft_printf("monitor thread created\n");
    pthread_mutex_unlock(&data->write_lock);
   
}  
// check if any philo died

// check fi the philosopher is dead