/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:02:34 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/26 09:59:51 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

//create a monitor thread and thread for each philo
void	ft_init_thread(t_data *data)
{
	pthread_t	t_monitor;
	int			i;
	t_philo		*c_philo;

	if (pthread_create(&t_monitor, NULL, &ft_m_routine, (void *)data) != 0)
		return((void)ft_printf("Error creating the monitor thread\n"));
	c_philo = data->first;
	i = 1;
	while (i++ <= data->p_nbr)
	{
		if (pthread_create(&c_philo->thread, NULL, \
		&ft_p_routine, (void *)c_philo) != 0)
			return((void)ft_printf("Error creating the philosopher thread\n"));
		c_philo = c_philo->next;
	}
	if (pthread_join(t_monitor, NULL) != 0)
		return((void)ft_printf("Error joining the monitor thread\n"));
	c_philo = data->first;
	i = 1;
	while (i++ <= data->p_nbr)
	{
		if (pthread_join(c_philo->thread, NULL) != 0)
			return((void)ft_printf("Error joining the philosopher thread\n"));
		c_philo = c_philo->next;
	}
}

//create the philos routine
void	*ft_p_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (ft_philo_dead(philo) == 0)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (pointer);
}

//checks if the philo is dead
int	ft_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
		return (pthread_mutex_unlock(&philo->data->dead_lock), 1);
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}
