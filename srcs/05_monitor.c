/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:12:00 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/16 19:11:03 by emimenza         ###   ########.fr       */
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
    
    ft_usleep(1000);
    while (1)
    {
        if (ft_any_philo_dead(data) == 1 || ft_check_all_ate(data) == 1)
        {
            pthread_mutex_lock(&data->dead_lock);
            data->dead_flag = 1;
            pthread_mutex_unlock(&data->dead_lock);
            break ;
        }
          
    }

    return (pointer);
}

// check if any philo is dead
int     ft_any_philo_dead(t_data *data)
{
    t_philo     *current_philo;

    current_philo = data->first;    
    while (1)
    {
        if (ft_philo_starved(current_philo, data->die_time) == 1)
        {
            ft_print_msg("has died",current_philo->id, current_philo);
            current_philo->dead = 1;
            return (1);
        }
        current_philo = current_philo->next;
        if (current_philo == data->first)
            break;
    }
    return (0);
}

//check if the philo  starved
int ft_philo_starved(t_philo *philo, int die_time)
{
    pthread_mutex_lock(&philo->meal_lock);
    if (((get_current_time() - philo->last_meal) >= die_time) && philo->eating == 0)
    {
        pthread_mutex_unlock(&philo->meal_lock);
        return (1);
    }
    pthread_mutex_unlock(&philo->meal_lock);
    return (0);
}

// check fif all the philo ate
int     ft_check_all_ate(t_data *data)
{
    t_philo     *current_philo;

    current_philo = data->first;    
    while (1)
    {
        if (current_philo->times_eat < data->eat_nbr)
        {
            return (0);
        }
        current_philo = current_philo->next;
        if (current_philo == data->first)
            break;
    }
    return (1);
}