/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:51:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/06 20:51:26 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;			//id of the philo
	pthread_t		thread;		//thread of the philo
	int				times_eat;  //times the philo has eaten
    size_t			last_meal;	//saves the last meal of a philo
	pthread_mutex_t	*right_fork;//right fork
	pthread_mutex_t	*left_fork;	//left fork
	struct s_philo	*next;		//pointer to the next philo
	struct s_philo	*prev;		//pointer to the prev philo
	struct s_data	*data;		//pointer to the data struct
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
	int				start_flag;	//flag to check if all the thread had been init
	pthread_mutex_t	lock;	//mutex to lock the dead flag of data
}					t_data;

int	ft_atoi(const char *str);
t_philo	*ft_last_node(t_philo *philo);
int	check_input(char **av);
size_t	get_current_time(void);
void    ft_start_program(t_data *data);
void	ft_usleep(int time);
void	ft_destroy_mutex(t_data **data);

#endif