/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:01:24 by psanger           #+#    #+#             */
/*   Updated: 2024/02/14 16:17:41 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_flag(t_philo *philo)
{
	if (philo->data->death == 0)
		return (0);
	return (1);
}

int	check_for_death(t_philo *philo)
{
	if (get_curr_time() - philo->time_last_meal > philo->data->time_to_die)
	{
		printf("%lu %d died\n", get_time(philo->og_time), philo->id);
		pthread_mutex_lock(philo->data->death_lock);
		philo->data->death = 0;
		pthread_mutex_unlock(philo->data->death_lock);
		return (0);
	}
	return (1);
}

int	philo_death(t_philo *philo)
{
	if (check_death_flag(philo) == 0 || check_for_death(philo) == 0)
		return (0);
	return (1);
}
