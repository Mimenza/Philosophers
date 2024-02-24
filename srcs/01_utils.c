/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:33:56 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/24 22:58:14 by emimenza         ###   ########.fr       */
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

int	get_time(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

void	ft_usleep(int time)
{
	long start;

	start = get_time(NULL);
	while (get_time(NULL) < start + time)
		usleep(10);
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
