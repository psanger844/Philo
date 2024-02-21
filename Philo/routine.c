/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:28:01 by psanger           #+#    #+#             */
/*   Updated: 2024/02/21 21:10:52 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_philo(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->death == 0)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (0);
	}
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->death == 1)
		printf("%lu %d %s\n", get_time(philo->og_time), philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->death_lock);
	return (1);
}

int	nbr_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meals_lock);
	philo->data->meals++;
	pthread_mutex_unlock(&philo->data->meals_lock);
	if (philo->data->number_of_meals)
	{
		pthread_mutex_lock(&philo->data->meals_lock);
		if (philo->data->meals >= (philo->data->number_of_meals + 0)
			* philo->data->number_of_philos)
		{
			pthread_mutex_unlock(&philo->data->meals_lock);
			pthread_mutex_lock(&philo->data->death_lock);
			philo->data->death = 0;
			pthread_mutex_unlock(&philo->data->death_lock);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->meals_lock);
		return (1);
	}
	return (1);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->death == 0)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	ft_print_philo(philo, "has taken a fork");
	ft_print_philo(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->time_last_meal_lock);
	philo->time_last_meal = get_curr_time();
	pthread_mutex_unlock(&philo->data->time_last_meal_lock);
	ft_print_philo(philo, "is eating");
	ft_sleep(philo->data->time_to_eat);
	if (nbr_meals(philo) == 0)
		return (0);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

int	philo_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->death == 0)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	ft_print_philo(philo, "is sleeping");
	ft_sleep(philo->data->time_to_sleep);
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->death == 0)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	ft_print_philo(philo, "is thinking");
	return (1);
}

void	*routine(void *args)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)args;
	if (philo->id % 2 == 1)
		usleep(100);
	pthread_mutex_lock(&philo->data->time_last_meal_lock);
	philo->time_last_meal = get_curr_time();
	pthread_mutex_unlock(&philo->data->time_last_meal_lock);
	while (philo->data->death)
	{
		if (philo_eat(philo) == 0)
			return (NULL);
		if (philo_sleep_think(philo) == 0)
			return (NULL);
	}
	return (NULL);
}
