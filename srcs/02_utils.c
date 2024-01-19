/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:13:02 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/16 18:52:34 by emimenza         ###   ########.fr       */
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

void	ft_print_data(t_data *data)
{
	ft_printf("---DATA--INFO---\n");
	ft_printf("number of philosophers %i\n", data->p_nbr);
	ft_printf("time to die %i\n", data->die_time);
	ft_printf("time to sleep %i\n", data->sleep_time);
	ft_printf("time to eat %i\n", data->eat_time);
	ft_printf("number of times each philosophers must eat %i\n", data->eat_nbr);
	ft_printf("dead flag %i\n", data->dead_flag);
	ft_printf("first philo id %i\n", data->first->id);
	ft_printf("last philo id %i\n", data->last->id);
	ft_printf("\n");
}

void	ft_print_philos(t_data *data)
{
	t_philo	*philo;

	philo = data->first;
	ft_printf("---PHILO--INFO---\n");
	while (1)
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
		ft_printf("left fork id %i\n", philo->left_fork->id);
		ft_printf("right fork id %i\n", philo->right_fork->id);
		ft_printf("-----\n");
		philo = philo->next;
		if (philo->id == data->first->id)
			break;
	}
}

void	ft_print_msg(char *str, int id, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_current_time();
    printf("the philo %d %s time: %zu\n", id, str, time);
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
	struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
	{
        perror("gettimeofday() error");
    	return 0;
    }
    return time.tv_sec * 1000 + time.tv_usec / 1000;
}

void	ft_destroy_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);

	t_philo	*philo;

	philo = data->first;
	while (1)
    {
		pthread_mutex_destroy(&philo->dead_lock);
		pthread_mutex_destroy(&philo->meal_lock);
		pthread_mutex_destroy(&philo->right_fork->fork_mutex);
		philo = philo->next;
		if (philo->id == data->first->id)
			break;
	}
}