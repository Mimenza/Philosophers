/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:02:34 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/13 14:22:08 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

//create a monitor thread and thread for each philo
void    ft_init_thread(t_data *data)
{
    pthread_t   t_monitor;
    int         i;
    t_philo     *current_philo; 

    //create the monitor routine thread
    if (pthread_create(&t_monitor, NULL, &ft_monitor_routine, (void *)data) != 0)
        ft_printf("error");
    
    current_philo = data->first;
    i = 1;
    
    //create the philosophers routine threads
    while (i <= data->p_nbr)
    {
        if (pthread_create(&current_philo->thread, NULL, &ft_philo_routine, (void *)current_philo) != 0)
            ft_printf("error");
        current_philo = current_philo->next;
        i++;
    }
    
    //join the monitor routine thread
    if (pthread_join(t_monitor, NULL) != 0)
        ft_printf("error");
    
    current_philo = data->first;
    i = 1;
    
    //join the philosphers routine threads
    while (i <= data->p_nbr)
    {
        if (pthread_join(current_philo->thread, NULL) != 0)
            ft_printf("error");
        current_philo = current_philo->next;
        i++;
    }
    
}
//create the philos routine
void    *ft_philo_routine(void *pointer)
{
    t_philo *philo;

    philo = (t_philo *)pointer;
    pthread_mutex_lock(&philo->data->write_lock);
    ft_printf("id = %d\n", philo->id);
    pthread_mutex_unlock(&philo->data->write_lock);
}
//checks if the philo is dead