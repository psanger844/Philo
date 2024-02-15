/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:28:01 by psanger           #+#    #+#             */
/*   Updated: 2024/02/14 16:21:32 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	philo_eat(t_philo *philo)
{
	if (philo_death(philo) == 0)
		return (0);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	if (philo_death(philo) == 0)
		return (0);
	printf("%lu %d has taken a fork\n", get_time(philo->og_time), philo->id);
	printf("%lu %d has taken a fork\n", get_time(philo->og_time), philo->id);
	philo->time_last_meal = get_curr_time();
	printf("%lu %d is eating\n", get_time(philo->og_time), philo->id);
	ft_sleep(philo->data->time_to_eat);
	if (philo_death(philo) == 0)
		return (0);
	pthread_mutex_lock(philo->data->meals_lock);
	philo->data->meals++;
	pthread_mutex_unlock(philo->data->meals_lock);


	if (philo->data->meals >= philo->data->number_of_meals * philo->data->number_of_philos)
	{
		pthread_mutex_lock(philo->data->death_lock);
		philo->data->death = 0;
		pthread_mutex_unlock(philo->data->death_lock);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}			// wenn die alle meals gemacht wurden wird abgebrochen mit death flag;


	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
	// eating finished
}

int	philo_sleep(t_philo *philo)
{
	if (philo_death(philo) == 0)
		return (0);

	printf("%lu %d is sleeping\n", get_time(philo->og_time), philo->id);
	ft_sleep(philo->data->time_to_sleep);
	return (1);
	// sleeping finished
}

int	philo_think(t_philo *philo)
{
	if (philo_death(philo) == 0)
		return (0);
	// thinking
	printf("%lu %d is thinking\n", get_time(philo->og_time), philo->id);
	return (1);
}

void* routine(void *args)
{
	int i;
	t_philo *philo;

	i = 0;

	philo = (t_philo *)args;

	if (philo->id % 2 == 1)
		usleep(500);
	if (philo->id % 2 == 0)
		usleep(250);
	philo->og_time = get_curr_time();
	philo->time_last_meal = get_curr_time();
	while (philo->data->death)
	{
		if (philo_eat(philo) == 0)
			return (NULL);
		if (philo_sleep(philo) == 0)
			return (NULL);
		if (philo_think(philo) == 0)
			return (NULL);
	}

	return (NULL);
}
