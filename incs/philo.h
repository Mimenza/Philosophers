/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:51:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/29 09:43:41 by emimenza         ###   ########.fr       */
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
	int				id;			//id of the fork
	pthread_mutex_t	fork_mutex; //Mutex to protect each fork
}					t_fork;

typedef struct s_philo
{
	int				id;			//id of the philo
	pthread_t		thread;		//thread of the philo
	int				eating;		//id if is eating
	int				sleeping;	//id if is sleeping
	int				thinking;	//id if is thinking
	int				times_eat;
	struct s_fork	*right_fork;//right fork
	struct s_fork	*left_fork;	//left fork
	struct s_philo	*prev;		//pointer to the prev philo
	struct s_philo	*next;		//pointer to the next philo
	struct s_data	*data;		//pointer to the data struct
	size_t			last_meal;	//saves the last meal of a philo
}					t_philo;

typedef struct s_data
{
	struct s_philo	*first;		//pointer to the first philo
	struct s_philo	*last;		//pointer to the last philo
	int				p_nbr;		//number of philos
	int				die_time;	//the time a philo has before dying
	int				sleep_time;	//the time a philo has to sleep
	int				eat_time;	//the time a philo has to eat
	int				eat_nbr;	//the times a philo need to eat
	int				dead_flag;	//flag to save the state if any philo died
	pthread_mutex_t	dead_lock;	//mutex to lock the dead flag of data
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;	//mutex to lock the write
}					t_data;

//main
int		ft_isnbr(char *str);
int		ft_check_arg(int argc, char **argv);

//init
void	ft_init_data(t_data **data, char **argv);
void	ft_create_philos(t_philo **philo, int id, t_data *data);
void	ft_init_philos(t_data *data, t_philo **philo);
void	ft_init_forks(t_fork **fork, int id, t_philo *new, t_philo *last);

//utils
t_philo	*ft_last_node(t_philo *philo);
void	ft_print_data(t_data *data);
void	ft_print_philos(t_data *data);
void	ft_init_program(t_data **data, t_philo **philo, char **argv);
void	ft_print_msg(char *str, int id, t_philo *philo);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
void	ft_destroy_mutex(t_data *data);

//thread
void	ft_init_thread(t_data *data);
void	*ft_p_routine(void *pointer);
int		ft_philo_dead(t_philo *philo);

//monitor
void	*ft_m_routine(void *pointer);
int		ft_any_philo_dead(t_data *data);
int		ft_check_all_ate(t_data *data);
int		ft_philo_starved(t_philo *philo, int die_time);

//actions
void	ft_think(t_philo *philo);
void	ft_sleep(t_philo *philo);
int		ft_eat(t_philo *philo);
#endif