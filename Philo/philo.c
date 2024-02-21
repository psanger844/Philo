/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:49:59 by psanger           #+#    #+#             */
/*   Updated: 2024/02/21 21:52:48 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_create(&data->threads[i], NULL, &routine,
				&data->philo[i]) != 0)
		{
			printf("Problem with creating thread %d\n", i);
			mid_free(data);
			return (0);
		}
		i++;
	}
	return (1);
}

void	check_time_pt2(t_data *data, int i)
{
	pthread_mutex_lock(&data->time_last_meal_lock);
	if (get_curr_time()
		- data->philo[i].time_last_meal >= (unsigned long)data->time_to_die)
	{
		printf("%lu %d died\n", get_time(data->philo[i].og_time), i);
		pthread_mutex_lock(&data->death_lock);
		data->death = 0;
		pthread_mutex_unlock(&data->death_lock);
	}
	pthread_mutex_unlock(&data->time_last_meal_lock);
}

void	check_time(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->death_lock);
		if (data->death == 0)
		{
			pthread_mutex_unlock(&data->death_lock);
			return ;
		}
		pthread_mutex_unlock(&data->death_lock);
		if (i >= data->number_of_philos)
			i = 0;
		check_time_pt2(data, i);
		i++;
		usleep(100);
	}
}

int	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
		{
			printf("Problem with waiting for thread %d\n", i);
			mid_free(data);
			return (0);
		}
		i++;
	}
	return (1);
}

int	philo(t_data *data)
{
	int	i;

	i = 0;
	data->threads = malloc(sizeof(pthread_t) * data->number_of_philos);
	if (data->threads == NULL)
		return (mid_free(data));
	if (data->number_of_philos <= 1)
	{
		data->philo->og_time = get_curr_time();
		if (ft_print_philo(data->philo, "has taken a fork") == 0)
			return (0);
		ft_sleep(data->time_to_die);
		if (ft_print_philo(data->philo, "has died") == 0)
			return (0);
		return (1);
	}
	i = -1;
	while (++i < data->number_of_philos)
		data->philo[i].og_time = get_curr_time();
	create_philos(data);
	check_time(data);
	join_philos(data);
	free(data->threads);
	return (1);
}
