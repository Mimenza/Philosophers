/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:33:56 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/25 18:22:03 by emimenza         ###   ########.fr       */
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
void ft_usleep(int time)
{
    struct timeval start_time, end_time, current_time;
    long time_left;

    gettimeofday(&start_time, NULL);
    end_time.tv_sec = start_time.tv_sec + (time / 1000);
    end_time.tv_usec = start_time.tv_usec + ((time % 1000) * 1000);

    if (end_time.tv_usec >= 1000000)
    {
        end_time.tv_sec += end_time.tv_usec / 1000000;
        end_time.tv_usec %= 1000000;
    }

    while (1)
    {
        gettimeofday(&current_time, NULL);
        time_left = (end_time.tv_sec - current_time.tv_sec) * 1000000 + (end_time.tv_usec - current_time.tv_usec);
        if (time_left <= 0)
            break;
        usleep(time_left);
    }
}

//Returns the current time 
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
