/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:13:02 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/11 16:46:49 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

t_philo	*ft_last_node(t_philo *philo)
{
	while (philo)
	{
		if (!philo->next)
			return (philo);
		philo = philo->next;
	}
	return (philo);
}

void	ft_print_data(t_data data)
{
	ft_printf("---DATA--INFO---\n");
	ft_printf("number of philosophers %i\n", data.p_nbr);
	ft_printf("time to die %i\n", data.die_time);
	ft_printf("time to eat %i\n", data.die_time);
	ft_printf("time to sleep %i\n", data.sleep_time);
	ft_printf("number of times each philosophers must eat %i\n", data.eat_nbr);
	ft_printf("first philo id %i\n", data.first->id);
	ft_printf("last philo id %i\n", data.last->id);
	
	
	ft_printf("\n");
}

void	ft_print_philos(t_philo *philo, t_data *data)
{
	ft_printf("---PHILO--INFO---\n");
	while (philo != data->last)
	{
		ft_printf("-----\n");
		ft_printf("id %i\n", philo->id);
		ft_printf("thread\n");
		ft_printf("eating %i\n", philo->eating);
		ft_printf("sleeping %i\n",philo->sleeping);
		ft_printf("thinking %i\n", philo->thinking);
		ft_printf("dead %i\n", philo->dead);
		ft_printf("prev id %i\n", philo->prev->id);
		ft_printf("next id %i\n", philo->next->id);
		philo = philo->next;
		ft_printf("-----\n");
	}
	ft_printf("-----\n");
	ft_printf("id %i\n", philo->id);
	ft_printf("thread\n");
	ft_printf("eating %i\n", philo->eating);
	ft_printf("sleeping %i\n",philo->sleeping);
	ft_printf("thinking %i\n", philo->thinking);
	ft_printf("dead %i\n", philo->dead);
	ft_printf("prev id %i\n", philo->prev->id);
	ft_printf("next id %i\n", philo->next->id);
	ft_printf("-----\n");
}