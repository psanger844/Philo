/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:26:53 by psanger           #+#    #+#             */
/*   Updated: 2024/02/21 20:16:27 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(int time_to_wait)
{
	unsigned long	time;
	struct timeval	curr;
	unsigned long	time_new;

	time = 0;
	if (gettimeofday(&curr, NULL) == 0)
		time = curr.tv_sec * 1000 + curr.tv_usec / 1000;
	while (1)
	{
		usleep(200);
		if (gettimeofday(&curr, NULL) == 0)
			time_new = curr.tv_sec * 1000 + curr.tv_usec / 1000;
		if (time_new - time >= (unsigned long)time_to_wait)
			break ;
	}
}

unsigned long	get_time(unsigned long og_time)
{
	struct timeval	curr;
	unsigned long	time;

	time = 0;
	if (gettimeofday(&curr, NULL) == 0)
		time = curr.tv_sec * 1000 + curr.tv_usec / 1000;
	return (time - og_time);
}

unsigned long	get_og_time(void)
{
	struct timeval	curr;
	unsigned long	og_time;

	og_time = 0;
	if (gettimeofday(&curr, NULL) == 0)
		og_time = curr.tv_sec * 1000 + curr.tv_usec / 1000;
	return (og_time);
}

unsigned long	get_curr_time(void)
{
	struct timeval	curr;
	unsigned long	time;

	time = 0;
	if (gettimeofday(&curr, NULL) == 0)
		time = curr.tv_sec * 1000 + curr.tv_usec / 1000;
	return (time);
}
