/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:51:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/11 15:16:10 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libs/ft_printf/ft_printf.h"
# include "../libs/Libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>


typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				eating;
	int				sleeping;
	int				thinking;
	int				dead;
	struct s_philo	*prev;
	struct s_philo	*next;
}					t_philo;

typedef struct s_data
{
	struct s_philo	*first;
	struct s_philo	*last;
	int				p_nbr;
	int				die_time;
	int				sleep_time;
	int				eat_time;
	int				eat_nbr;
}					t_data;

//main
int		ft_isnbr(char *str);
int		ft_check_arg(int argc, char **argv);

//init
t_data	*ft_init_data(char *philo_nbr, char *die_time, char *sleep_time, char *eat_time, char *eat_nbr);
void	ft_init_philos(t_philo **philo, int id);

//utils
t_philo	*ft_last_node(t_philo *philo);
void	ft_print_data(t_data data);

#endif