/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:34:23 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/16 18:55:47 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

//check if the str is only made of nbr
int	ft_isnbr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

//check all the args
int	ft_check_arg(int argc, char **argv)
{
	if (ft_isnbr(argv[1]) == 1 || ft_atoi(argv[1]) == 1)
		return (ft_printf("Error [number_of_philosophers] argument\n"), 1);
	if (ft_isnbr(argv[2]) == 1)
		return (ft_printf("Error [time_to_die] argument\n"), 1);
	if (ft_isnbr(argv[3]) == 1)
		return (ft_printf("Error [time_to_eat] argument\n"), 1);
	if (ft_isnbr(argv[4]) == 1)
		return (ft_printf("Error [time_to_sleep] argument\n"), 1);
	if (argv[5] && ft_isnbr(argv[5]) == 1)
		return (ft_printf("Error [number_of_times_each_philosopher_must_eat] \
		argument\n"), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_data			*data;
	
	if (argc != 5 && argc != 6)
		return (ft_printf("Wrong number of arguments\n"), 0);
	if (ft_check_arg(argc, argv) == 1)
		return (0);
	ft_init_program(&data, &philo, argv);
	//ft_print_data(data);
	//ft_print_philos(data);

	ft_init_thread(data);
	//destroy the mutex
	ft_destroy_mutex(data);
	return (0);
}
