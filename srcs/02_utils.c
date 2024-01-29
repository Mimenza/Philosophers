/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:13:02 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/29 10:01:58 by emimenza         ###   ########.fr       */
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

void	ft_print_msg(char *str, int id, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_current_time();
	printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	static clock_t	inicio;
	clock_t			actual;

	if (inicio == 0)
	{
		inicio = clock();
		return (0);
	}
	else
	{
		actual = clock();
		return ((size_t)((actual - inicio) * 1000 / CLOCKS_PER_SEC));
	}
}

void	ft_destroy_mutex(t_data *data)
{
	t_philo	*philo;
	t_philo	*next_philo;

	philo = data->first;
	while (1)
	{
		pthread_mutex_destroy(&philo->right_fork->fork_mutex);
		if (philo->right_fork)
			free (philo->right_fork);
		next_philo = philo->next;
		free(philo);
		philo = next_philo;
		if (philo == data->first)
			break ;
	}
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
	free(data);
}
