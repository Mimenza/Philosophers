/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:34:23 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/24 23:01:41 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//FALTA 
//LIBERAR MEMORIA DE LOS PHILOS
//SEG FAULT CON PHILO NBR = 0

#include "../incs/philo.h"

//Inits the  data structure
void	ft_init_data(t_data **data, char **argv)
{
	*data = malloc(sizeof(t_data));
	if (*data == NULL)
		return ;
	(*data)->p_nbr = ft_atoi(argv[1]);
	(*data)->die_time = ft_atoi(argv[2]);
	(*data)->eat_time = ft_atoi(argv[3]);
	(*data)->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		(*data)->eat_nbr = ft_atoi(argv[5]);
	else
		(*data)->eat_nbr = -1;
	(*data)->dead_flag = 0;
	(*data)->start_flag = 0;
	pthread_mutex_init(&((*data)->lock), NULL);
	return ;
}

//Inits the philo structure
void	ft_create_philos(t_philo **philo, int id, t_data *data)
{
	t_philo			*new;
	t_philo			*last;

	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return ;
	if (*philo == NULL)
	{
		*philo = new;
		new->prev=NULL;
		new->left_fork = NULL;
	}
	else
	{
		last = ft_last_node(*philo);
		last->next = new;				
		new->prev = last;
		new->left_fork = last->right_fork;
	}
	new->id = id;
	new->times_eat = 0;
	new->data = data;
	new->last_meal = 0;
	new->right_fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->right_fork, NULL);
}

void	ft_init_philos(t_data *data, t_philo **philo)
{
	int		id;
	t_philo	*first_p;
	t_philo	*last_p;

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
		if (data->p_nbr != 1)
			first_p->left_fork = last_p->right_fork;
		data->first = first_p;
		data->last = last_p;
	}
}

//Inits the data and philo structures
void	ft_init_program(t_data **data, t_philo **philo, char **argv)
{
	ft_init_data(data, argv);
	ft_init_philos(*data, philo);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;
	
	data = NULL;
	philo = NULL;
	if (argc < 5 || argc > 6)
		return (printf("Invalid parameters\n"), 0);
	if (check_input(&argv[1]) == 1)
		return (printf("Invalid character\n"), 0);
	if (ft_atoi(argv[1]) > 250)
		return (printf("Too many philosophers"), 0);
	ft_init_program(&data, &philo, argv);
	ft_start_program(data);
	ft_destroy_mutex(data);
	return (0);
}
