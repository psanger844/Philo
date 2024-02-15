/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:57:59 by psanger           #+#    #+#             */
/*   Updated: 2024/02/06 13:51:09 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_sleep(int time_to_wait)
{
	long			time;
	struct timeval	currtest;
	long			time_new;

	if (gettimeofday(&currtest, NULL) == 0)
	{
		time = currtest.tv_sec * 1000 + currtest.tv_usec / 1000;
	}
	while (1)
	{
		usleep(100);
		if (gettimeofday(&currtest, NULL) == 0)
		{
			time_new = currtest.tv_sec * 1000 + currtest.tv_usec / 1000;
		}
		else
		{
			printf("Fehler!!\n");
		}
		if (time_new - time >= time_to_wait)
			break ;
	}
}

void	*routine(void *param)
{
	t_philo			*philo;
	long			time_new;
	struct timeval	currtest;

	philo = param;
	pthread_mutex_lock(philo->mutex);
	if (gettimeofday(&currtest, NULL) == 0)
	{
		time_new = currtest.tv_sec * 1000 + currtest.tv_usec / 1000;
	}
	printf("Time thread = %ld\n", (time_new - (long)philo->time));
	// usleep(300000);
	ft_sleep(300);
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				num_philos;
	struct timeval	curr;
	pthread_t		*threads;
	long			time_seconds;
	long			time_mikroseconds;
	long			time;
	t_philo			philo;

	if (argc <= 1)
	{
		printf("fehler mit argumenten\n");
		return (1);
	}
	num_philos = atoi(argv[1]);
	if (num_philos <= 0)
	{
		printf("fehler mit der Zahl\n");
		return (1);
	}
	threads = malloc(sizeof(pthread_t) * num_philos);
	if (gettimeofday(&curr, NULL) == 0)
		printf("Current time: %ld,%d seconds\n", curr.tv_sec, curr.tv_usec);
	time_seconds = curr.tv_sec;
	time_mikroseconds = curr.tv_usec;
	time = time_seconds * 1000 + time_mikroseconds / 1000;
	printf("%ld\n", time);
	philo.time = time;
	if (pthread_mutex_init(philo.mutex, NULL) != 0)
	{
		printf("Fehler mit dem init von mutex\n");
		return (1);
	}
	for (int i = 0; i < num_philos; i++)
	{
		if (pthread_create(&threads[i], NULL, &routine, &philo) != 0)
		{
			printf("Fehler beim erstellen\n");
			return (1);
		}
	}
	for (int i = 0; i < num_philos; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("Fehelr beim warten auf threads\n");
			return (1);
		}
	}
	free(threads);
	return (0);
}
