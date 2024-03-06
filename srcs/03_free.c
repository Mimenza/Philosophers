/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:02:34 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/06 20:44:15 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void ft_destroy_mutex(t_data **data)
{
    t_philo *philo = (*data)->first;
    t_philo *next_philo;

    while (philo)
    {
        next_philo = philo->next;
        pthread_mutex_destroy(philo->right_fork);
        free(philo->right_fork);
        free(philo);
        philo = next_philo;
        if (philo == (*data)->first)
            break;
    }
    pthread_mutex_destroy(&(*data)->lock);
    free(*data);
    *data = NULL;
}
