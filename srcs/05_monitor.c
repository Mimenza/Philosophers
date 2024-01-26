/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:12:00 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/26 09:52:17 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

// monitor thread routine
void	*ft_m_routine(void *pointer)
{
	t_data	*data;

	data = (t_data *)pointer;
	while (1)
	{
		if (ft_any_philo_dead(data) == 1 || ft_check_all_ate(data) == 1)
		{
			return (pointer);
		}
	}
	return (pointer);
}

// check if any philo is dead
int	ft_any_philo_dead(t_data *data)
{
	t_philo	*current_philo;

	current_philo = data->first;
	while (1)
	{
		if (ft_philo_starved(current_philo, data->die_time) == 1)
		{
			ft_print_msg("died", current_philo->id, current_philo);
			pthread_mutex_lock(&current_philo->data->dead_lock);
			current_philo->data->dead_flag = 1;
			pthread_mutex_unlock(&current_philo->data->dead_lock);
			return (1);
		}
		current_philo = current_philo->next;
		if (current_philo == data->first)
			break ;
	}
	return (0);
}

//check if the philo  starved
int	ft_philo_starved(t_philo *philo, int die_time)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	if (((get_current_time() - philo->last_meal) >= die_time) \
	&& philo->eating == 0)
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (0);
}

// check fif all the philo ate
int	ft_check_all_ate(t_data *data)
{
	t_philo	*current_philo;
	int		finish_eating;

	finish_eating = 0;
	if (data->eat_nbr == -1)
		return (0);
	current_philo = data->first;
	while (1)
	{
		pthread_mutex_lock(&current_philo->data->meal_lock);
		if (current_philo->times_eat >= data->eat_nbr)
			finish_eating++;
		pthread_mutex_unlock(&current_philo->data->meal_lock);
		current_philo = current_philo->next;
		if (current_philo == data->first)
			break ;
	}
	if (finish_eating == data->p_nbr)
	{
		pthread_mutex_lock(&current_philo->data->dead_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(&current_philo->data->dead_lock);
		return (1);
	}
	return (0);
}
