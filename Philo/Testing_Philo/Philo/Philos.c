/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:56:55 by psanger           #+#    #+#             */
/*   Updated: 2024/02/06 23:19:53 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philo, int num_philos, t_data *data)
{
	int i = 0;
	if (num_philos <= 0)
		exit(1);
	while (i < num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			for (int j = 0; j < i; j++)
				pthread_mutex_destroy(&data->forks[j]);
			exit(1);
		}
		i++;
	}
	i = 1;
	philo[i].id = i;
	philo[i].left_fork = 0;
	philo[i].right_fork = data->forks;
	while (i < num_philos)
	{
		philo[i].id = i;
		philo[i].left_fork = philo[i - 1].right_fork;
		philo[i].right_fork = data->forks;
		i++;
	}
	philo[0].left_fork = philo[num_philos -1].right_fork;
	// i = 0;
	// while (i < num_philos)
	// {
	// 	printf("id : %d\n", philo[i].id);
	// 	printf("links : %p\n", philo[i].left_fork);
	// 	printf("rechts : %p\n", philo[i].right_fork);
	// 	printf("------------------------\n");
	// 	i++;
	// }
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	// pthread_mutex_lock(philo->left_fork);
	// pthread_mutex_lock(philo->right_fork);
	printf("test %d\n", philo->id);
	usleep(300000);

	// pthread_mutex_unlock(philo->left_fork);
	// pthread_mutex_unlock(philo->right_fork);

	return NULL;
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	int	num_philos = atoi(argv[1]);
	t_philo	*philo;
	t_data *data = malloc(sizeof(t_data));
	philo = malloc(sizeof(t_philo) * num_philos);
	data->philo = philo;
	data->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	int	i = 0;

	init_philos(philo, num_philos, data);
	pthread_t *threads = malloc(sizeof(pthread_t) * num_philos);
	for (int i = 0; i < num_philos; i++)
	{
		// printf("AHHHHHH %d %d\n", data->philo[i].id, num_philos);
		if (pthread_create(&threads[i], NULL, &routine, &data->philo[i]) != 0)
		{
			printf("Problem beim erstellen %d\n", i);
			exit (1);
		}
	}
	for (int i = 0; i < num_philos; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("Probmlem beim warten %d\n", i);
			exit (1);
		}
	}
	free(data->forks);
	free (threads);
	free(philo);
	return (0);
}
