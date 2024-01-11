/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:33:56 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/11 15:16:48 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"


t_data	*ft_init_data(char *philo_nbr, char *die_time, char *sleep_time, char *eat_time, char *eat_nbr)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (data);
	data->p_nbr = ft_atoi(philo_nbr);
	data->die_time = ft_atoi(die_time);
	data->sleep_time = ft_atoi(sleep_time);
	data->eat_time = ft_atoi(eat_time);
	if (eat_nbr)
		data->eat_nbr = ft_atoi(eat_nbr);
	else
		data->eat_nbr = 0;
	return (data);
}

void	ft_init_philos(t_philo **philo, int id)
{
	t_philo		*new;
	t_philo		*last;
	pthread_t	thread;
	

	if (philo == NULL)
		return ;
	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return ;
	if (*philo == NULL)
	{
		*philo = new;
		new->prev = NULL;
	}
	else
	{
		last = ft_last_node(*philo);
		last->next = new;
		new->prev = last;
	}
	//fill al the philos data;
	new->dead = 0;
	new->eating = 0;
	new->sleeping = 0;
	new->thinking = 0;
	new->id = id;
}