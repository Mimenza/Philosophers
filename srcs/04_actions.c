/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:03:04 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/29 09:43:00 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

// think routine
void	ft_think(t_philo *philo)
{
	philo->thinking = 1;
	ft_print_msg("is thinking", philo->id, philo);
	philo->thinking = 0;
}

// dream routine
void	ft_sleep(t_philo *philo)
{
	philo->sleeping = 1;
	ft_print_msg("is sleeping", philo->id, philo);
	ft_usleep(philo->data->sleep_time);
	philo->sleeping = 0;
}

// eat routine
int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	ft_print_msg("has taken a fork", philo->id, philo);
	if (philo->left_fork == NULL)
		return (0);
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	ft_print_msg("has taken a fork", philo->id, philo);
	philo->eating = 1;
	ft_print_msg("is eating", philo->id, philo);
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	philo->last_meal = get_current_time();
	philo->times_eat += 1;
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	return (1);
}
