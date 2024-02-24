/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:02:34 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/24 22:59:44 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	ft_destroy_mutex(t_data *data)
{
	t_philo	*philo;
	t_philo	*next_philo;

	philo = data->first;
	while (1)
	{
		next_philo = philo->next;
		free(philo);
		philo = next_philo;
		
		if (philo == data->first)
			break ;
	}
	free(data);
}