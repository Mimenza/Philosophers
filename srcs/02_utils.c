/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:13:02 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/11 15:15:39 by emimenza         ###   ########.fr       */
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
	ft_printf("die time %i\n", data.die_time);
	ft_printf("eat number %i\n", data.eat_nbr);
	ft_printf("eat time %i\n", data.eat_time);
	ft_printf("player number %i\n", data.p_nbr);
	ft_printf("die time %i\n", data.die_time);
}