/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:13:02 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/07 10:06:01 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

//Prints the msg when all the philos are alive
void	ft_print_msg(char *msg, t_philo *philo)
{
	if (philo->data->dead_flag == 0)
	{
		printf("%li %i %s\n", get_current_time(), philo->id, msg);
	}
}

//Aux philo routine
int	ft_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->lock);
	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(philo->right_fork);
	ft_print_msg("has taken a fork", philo);
	if (philo->left_fork == NULL)
		return (pthread_mutex_unlock(philo->right_fork), 0);
	pthread_mutex_lock(philo->left_fork);
	ft_print_msg("has taken a fork", philo);
	ft_print_msg("is eating", philo);
	ft_usleep(philo->data->eat_time);
	philo->last_meal = get_current_time();
	philo->times_eat++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	usleep(2000);
	ft_print_msg("is sleeping", philo);
	ft_usleep(philo->data->sleep_time);
	ft_print_msg("is thinking", philo);
	return (1);
}

//Check if any philo is dead or if all have eat
int	ft_check_dead(t_data *data)
{
	int			i;
	static int	philo_eat;
	t_philo		*c_philo;

	i = 0;
	philo_eat = 0;
	c_philo = data->first;
	while (i < data->p_nbr)
	{
		if (((get_current_time() - c_philo->last_meal) > data->die_time) || \
		((c_philo->last_meal == 0) && (get_current_time() > data->die_time)))
		{
			ft_print_msg("died", c_philo);
			data->dead_flag = 1;
			return (1);
		}
		if ((data->eat_nbr >= 0) && (c_philo->times_eat == data->eat_nbr))
			philo_eat++;
		i++;
		c_philo = c_philo->next;
	}
	if (philo_eat == data->p_nbr)
		return (data->dead_flag = 1, 1);
	return (0);
}

//Main philo routine
void	*ft_philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if ((philo->data->dead_flag == 0 && philo->data->start_flag == 1) && \
		(philo->times_eat < philo->data->eat_nbr || philo->data->eat_nbr == -1))
			if (ft_routine(philo) == 0)
				return (0);
		usleep(1000);
		if (philo->data->dead_flag == 1)
			return (0);
	}
	return (0);
}

//Main program funtion
void	ft_start_program(t_data *data)
{
	int		i;
	t_philo	*c_philo;

	c_philo = (data)->first;
	i = 0;
	while (++i <= (data)->p_nbr)
	{
		if (pthread_create(&(c_philo)->thread, NULL, \
		&ft_philo_routine, (void *)c_philo) != 0)
			return ((void)printf("Error creating the monitor thread\n"));
		c_philo = c_philo->next;
	}
	data->start_flag = 1;
	while (ft_check_dead(data) == 0)
		;
	if (data->p_nbr == 1)
		return ;
	c_philo = (data)->first;
	i = 0;
	while (++i <= (data)->p_nbr)
	{
		if (pthread_join(c_philo->thread, NULL) != 0)
			return ((void)printf("Error joining the philosopher thread\n"));
		c_philo = c_philo->next;
	}
}
