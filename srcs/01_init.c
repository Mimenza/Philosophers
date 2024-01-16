/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:33:56 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/16 19:05:12 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	ft_init_data(t_data **data, char *philo_nbr, char *die_time, char *sleep_time, char *eat_time, char *eat_nbr)
{
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;

	(*data) = malloc(sizeof(t_data));
	if (data == NULL)
		return ;
	(*data)->p_nbr = ft_atoi(philo_nbr);
	(*data)->die_time = ft_atoi(die_time);
	(*data)->sleep_time = ft_atoi(sleep_time);
	(*data)->eat_time = ft_atoi(eat_time);
	if (eat_nbr)
		(*data)->eat_nbr = ft_atoi(eat_nbr);
	else
		(*data)->eat_nbr = 0;
	(*data)->dead_lock = dead_lock;
	(*data)->meal_lock = meal_lock;
	(*data)->write_lock = write_lock;
	(*data)->dead_flag = 0;

	pthread_mutex_init(&(*data)->write_lock, NULL);
	return ;
}

void	ft_create_philos(t_philo **philo, int id, t_data *data)
{
	t_philo			*new;
	t_philo			*last;
	t_fork			*fork;

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
	ft_init_forks(&fork, id, new, last);
	new->dead = 0;
	new->eating = 0;
	new->sleeping = 0;
	new->thinking = 0;
	new->id = id;
	new->times_eat = 0;
	new->data = data;
	new->last_meal = get_current_time();
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
		ft_create_philos(philo, id, data);
		if (first_p == NULL)
			first_p = (*philo);
		id++;
	}
	if (first_p != NULL)
	{
		last_p = ft_last_node(*philo);
		last_p->next = first_p;
		first_p->prev = last_p;
		first_p->left_fork = last_p->right_fork;
		
		data->first = first_p;
		data->last = last_p;
	}
}

void	ft_init_forks(t_fork **fork, int id, t_philo *new, t_philo *last)
{
	pthread_mutex_t	fork_lock;

	(*fork) = malloc(sizeof(t_fork));
	if ((*fork) == NULL)
		return;
	(*fork)->free = 1;
	(*fork)->id = id;
	(*fork)->fork_mutex = fork_lock;

	// init the mutex for the fork
	pthread_mutex_init(&(*fork)->fork_mutex, NULL);

	//linking the forks to the philos
	if (id == 1)
		new->left_fork = NULL;
	else
		new->left_fork = last->right_fork;
	new->right_fork = (*fork);
}

void	ft_init_program(t_data **data, t_philo **philo, char **argv)
{
	ft_init_data(data, argv[1], argv[2], argv[3], argv[4], argv[5]);
	ft_init_philos(*data, philo);
	
	// init the mutexes
	pthread_mutex_init(&(*data)->dead_lock, NULL);	//lock to protect the data while checking if any philo died
	pthread_mutex_init(&(*data)->meal_lock, NULL);	//lock to proyect the data while checking if the philo is dead (dont let that philo eat)
	pthread_mutex_init(&(*data)->write_lock, NULL);	//lock to protect the data while writing data on console
}
