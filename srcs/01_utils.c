/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:33:56 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/07 10:05:34 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

//Returs the last node of the list
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

//Custom usleep function
void	ft_usleep(int time)
{
	struct timeval	start_time;
	struct timeval	end_time;
	struct timeval	current_time;
	long			time_left;

	gettimeofday(&start_time, NULL);
	time -= 3;
	end_time.tv_sec = start_time.tv_sec + ((time) / 1000);
	end_time.tv_usec = start_time.tv_usec + (((time) % 1000) * 1000);
	if (end_time.tv_usec >= 1000000)
	{
		end_time.tv_sec += end_time.tv_usec / 1000000;
		end_time.tv_usec %= 1000000;
	}
	while (1)
	{
		gettimeofday(&current_time, NULL);
		time_left = (end_time.tv_sec - current_time.tv_sec) * \
		1000000 + (end_time.tv_usec - current_time.tv_usec);
		if (time_left <= 0)
			break ;
		usleep(time_left);
	}
}

size_t	get_current_time(void)
{
	static struct timeval	start_time = {0, 0};
	struct timeval			current_time;

	if (start_time.tv_sec == 0 && start_time.tv_usec == 0)
	{
		gettimeofday(&start_time, NULL);
		return (0);
	}
	else
	{
		gettimeofday(&current_time, NULL);
		return (((current_time.tv_sec - start_time.tv_sec) * 1000) + \
		((current_time.tv_usec - start_time.tv_usec) / 1000));
	}
}

//Atoi function
int	ft_atoi(const char *str)
{
	int	number;
	int	sign;
	int	i;

	number = 0;
	sign = 1;
	i = 0;
	while (*(str + i) == 32 || (*(str + i) >= 9 && *(str + i) <= 13))
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '+' || *(str + i) == '-')
		i++;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		number = number * 10 + (*(str + i) - 48);
		i++;
	}
	return (number * sign);
}

//Checks the input file
int	check_input(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[j])
	{
		while (av[j][i])
		{
			if (av[j][i] >= '0' && av[j][i] <= '9')
				i++;
			else
				return (1);
		}
		i = 0;
		j++;
	}
	return (0);
}
