/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:49:59 by psanger           #+#    #+#             */
/*   Updated: 2024/02/21 19:01:01 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos(t_data *data)
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
			exit(1);
		}
		i++;
	}
}

void	check_time(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_lock(&data->og_time_lock);
		data->philo[i].og_time = get_curr_time();
		pthread_mutex_unlock(&data->og_time_lock);
		i++;
	}
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
		pthread_mutex_lock(&data->time_last_meal_lock);
		if (get_curr_time()
			- data->philo[i].time_last_meal >= data->time_to_die)
		{
			printf("%lu %d died\n", get_time(data->philo[i].og_time), i);
			pthread_mutex_lock(&data->death_lock);
			data->death = 0;
			pthread_mutex_unlock(&data->death_lock);
		}
		pthread_mutex_unlock(&data->time_last_meal_lock);
		i++;
		usleep(200);
	}
}

void	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
		{
			printf("Problem with waiting for thread %d\n", i);
			mid_free(data);
			exit(1);
		}
		i++;
	}
}

void	philo(t_data *data)
{
	int	i;

	i = 0;
	data->threads = malloc(sizeof(pthread_t) * data->number_of_philos);
	if (data->threads == NULL)
		mid_free(data);
	if (data->number_of_philos <= 1)
	{
		data->philo->og_time = get_curr_time();
		ft_print_philo(data->philo, "has taken a fork");
		ft_sleep(data->time_to_die);
		ft_print_philo(data->philo, "has died");
		return ;
	}
	create_philos(data);
	check_time(data);
	join_philos(data);
	free(data->threads);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	if (args_checker(argc, argv) == 1)
	{
		printf("there are wrong chars in the arguments\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	init_data(argc, argv, data);
	init_philo(data);
	philo(data);
	final_free(data);
	free(data);
	return (0);
}
