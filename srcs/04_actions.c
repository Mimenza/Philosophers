/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:03:04 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/14 01:22:43 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

// think routine
void    ft_think(t_philo *philo)
{
    philo->thinking = 1;
    ft_print_msg("is thinking", philo->id, philo);
    philo->thinking = 0;
}

// dream routine
void    ft_sleep(t_philo *philo)
{
    philo->sleeping = 1;
    ft_print_msg("is sleeping", philo->id, philo);
    usleep(philo->data->sleep_time);
    philo->sleeping = 0;
}

// eat routine
void    ft_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->right_fork->fork_mutex);
    ft_print_msg("has a taken the right fork", philo->id, philo);
    
    pthread_mutex_lock(&philo->left_fork->fork_mutex);
    ft_print_msg("has a taken the left fork", philo->id, philo);
    
    //pthread_mutex_lock(&philo->data->meal_lock);
    philo->eating = 1;    
    ft_print_msg("is eating", philo->id, philo);
    //pthread_mutex_unlock(&philo->data->meal_lock);  
    usleep(philo->data->eat_time);
    
    philo->eating = 0;
    pthread_mutex_unlock(&philo->left_fork->fork_mutex);
    pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}