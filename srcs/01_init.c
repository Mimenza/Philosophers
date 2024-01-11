/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:33:56 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/11 16:41:45 by emimenza         ###   ########.fr       */
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

void	ft_create_philos(t_philo **philo, int id)
{
	t_philo		*new;
	t_philo		*last;
	//pthread_t	thread;
	
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
	new->dead = 0;
	new->eating = 0;
	new->sleeping = 0;
	new->thinking = 0;
	new->id = id;
}

void	ft_init_philos(t_data *data, t_philo **philo)
{
	int	id;
	t_philo *first_p;
	t_philo *last_p;

	first_p = NULL;
	last_p = NULL;
	id = 1;
	while (id <= data->p_nbr)
	{
		ft_create_philos(philo, id);
		if (first_p == NULL)
			first_p = (*philo);
		id++;
	}
	if (first_p != NULL)
	{
		last_p = ft_last_node(*philo);
		last_p->next = first_p;
		first_p->prev = last_p;
		data->first = first_p;
		data->last = last_p;
		ft_printf("first filo = %i \n", data->first->id);
		ft_printf("last filo = %i \n", data->last->id);
	}
}