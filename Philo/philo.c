/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:49:59 by psanger           #+#    #+#             */
/*   Updated: 2024/02/13 20:45:28 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos(t_data *data)
{
	int i;
	pthread_t *threads;

	i = 0;
	threads = malloc(sizeof(pthread_t) * data->number_of_philos);
	while (i < data->number_of_philos)
	{
		if (pthread_create(&threads[i], NULL, &routine, &data->philo[i]) != 0)
		{
			printf("Problem with creating thread %d\n", i);
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("Problem with waiting for thread %d\n", i);
			exit(1);
		}
		i++;
	}
	free(threads);
}

int main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf ("Wrong number of arguments!\n");
		return (1);
	}
	if (args_checker(argc, argv) == 1)
	{
		printf ("there are wrong chars in the arguments\n");
		return (1);
	}
	t_data *data;
	data = malloc(sizeof(t_data));
	init_data(argc, argv, data);
	init_philo(data);

	create_philos(data);

	free(data->philo);
	free(data);
	return (0);
}
