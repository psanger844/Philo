/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:50:45 by psanger           #+#    #+#             */
/*   Updated: 2024/02/14 15:56:13 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(int argc, char **argv, t_data *data)
{
	t_philo *philo;

	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->og_time = get_og_time();
	data->death = 1;
	data->meals = 0;
	data->meals_lock = malloc(sizeof(pthread_mutex_t));
	data->death_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->meals_lock, NULL);
	pthread_mutex_init(data->death_lock, NULL);
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	philo = malloc(sizeof(t_philo) * data->number_of_philos);
	data->philo = philo;
}


void	init_philo(t_data *data)
{
	t_philo *philo;
	pthread_mutex_t **fork;
	int	og_time;
	int i;

	fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	og_time = get_og_time();
	i = 0;
	while (i < data->number_of_philos)
	{
		fork[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(fork[i], NULL);
		i++;
	}
	for (i = 0; i < data->number_of_philos; i++) {
		data->philo[i].time_last_meal = 0;
		data->philo[i].data = data;
		data->philo[i].id = i;
		data->philo[i].og_time = og_time;
		data->philo[i].left_fork = fork[i];
		data->philo[i].right_fork = fork[(i + 1) % data->number_of_philos];
	}
}

// forks noch nicht free
