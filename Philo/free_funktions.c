/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funktions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:51:58 by psanger           #+#    #+#             */
/*   Updated: 2024/02/21 19:03:24 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mid_free(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meals_lock);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->og_time_lock);
	pthread_mutex_destroy(&data->time_last_meal_lock);
	if (data->philo)
		free(data->philo);
	if (data->threads)
		free(data->threads);
	if (data->fork)
	{
		while (i < data->number_of_philos)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i++;
		}
		pthread_mutex_destroy(data->fork);
		free(data->fork);
	}
	if (data)
		free(data);
	printf("someting went wrong (malloc / threads) \n");
	exit(1);
}

void	final_free(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meals_lock);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->og_time_lock);
	pthread_mutex_destroy(&data->time_last_meal_lock);
	while (i < data->number_of_philos)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(data->fork);
	free(data->fork);
	free(data->philo);
}
