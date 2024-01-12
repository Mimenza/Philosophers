/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:51:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/12 18:58:14 by emimenza         ###   ########.fr       */
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
# include <stdlib.h>

typedef struct s_fork
{
	int				id;
	int				free;
	pthread_mutex_t fork_mutex; //Mutex to protect each fork
}					t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				eating;
	int				sleeping;
	int				thinking;
	int				dead;
	struct s_fork	*right_fork;
	struct s_fork	*left_fork;
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
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}					t_data;

//main
int		ft_isnbr(char *str);
int		ft_check_arg(int argc, char **argv);

//init
void	ft_init_data(t_data **data, char *philo_nbr, char *die_time, char *sleep_time, char *eat_time, char *eat_nbr);
void	ft_create_philos(t_philo **philo, int id, t_data *data);
void	ft_init_philos(t_data *data, t_philo **philo);
void	ft_init_forks(t_fork **fork, int id, t_philo *new, t_philo *last);

//utils
t_philo	*ft_last_node(t_philo *philo);
void	ft_print_data(t_data *data);
void	ft_print_philos(t_philo *philo, t_data *data);
void	ft_init_program(t_data **data, t_philo **philo, char **argv);
#endif