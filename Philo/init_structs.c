/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:50:45 by psanger           #+#    #+#             */
/*   Updated: 2024/02/21 19:00:02 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(int argc, char **argv, t_data *data)
{
	t_philo	*philo;

	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->og_time = get_og_time();
	data->death = 1;
	data->meals = 0;
	pthread_mutex_init(&data->og_time_lock, NULL);
	pthread_mutex_init(&data->time_last_meal_lock, NULL);
	pthread_mutex_init(&data->meals_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->print, NULL);
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	else
		data->number_of_meals = 0;
	philo = malloc(sizeof(t_philo) * data->number_of_philos);
	if (philo == NULL)
		mid_free(data);
	data->philo = philo;
}

void	init_philo(t_data *data)
{
	int		i;
	int		og_time;

	og_time = get_og_time();
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (data->fork == NULL)
		mid_free(data);
	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		data->philo[i].time_last_meal = get_curr_time();
		data->philo[i].data = data;
		data->philo[i].id = i;
		data->philo[i].og_time = og_time;
		data->philo[i].left_fork = &data->fork[i];
		data->philo[i].right_fork = &data->fork[(i + 1)
			% data->number_of_philos];
		i++;
	}
}
