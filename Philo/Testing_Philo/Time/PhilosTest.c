/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhilosTest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:38:29 by psanger           #+#    #+#             */
/*   Updated: 2024/02/06 13:39:37 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int main(int argc, char **argv)
{
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
