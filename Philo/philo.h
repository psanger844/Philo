/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:50:41 by psanger           #+#    #+#             */
/*   Updated: 2024/02/14 16:11:43 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct			s_philo
{
	int					id;
	unsigned long		og_time;
	unsigned long		time_last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_data		*data;
}						t_philo;


typedef struct			s_data
{
	t_philo				*philo;
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	int					og_time;
	int					death;
	int					meals;
	pthread_mutex_t		*meals_lock;
	pthread_mutex_t		*death_lock;
}						t_data;

// helper funktions

int	args_checker(int argc, char **argv);
int	ft_atoi(const char *str);

// init

void	init_data(int argc, char **argv, t_data *data);
void	init_philo(t_data *data);


// time

void			ft_sleep(int time_to_wait);
unsigned long	get_time(unsigned long og_time);
unsigned long	get_og_time(void);
unsigned long	get_curr_time();

// routine

void* routine(void *args);

int	philo_eat(t_philo *philo);
int	philo_sleep(t_philo *philo);
int	philo_think(t_philo *philo);

// death check

int	philo_death(t_philo *philo);



#endif
