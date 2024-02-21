/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:17:58 by psanger           #+#    #+#             */
/*   Updated: 2024/02/21 21:49:52 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (init_data(argc, argv, data) == 0)
		return (0);
	if (init_philo(data) == 0)
		return (0);
	if (philo(data) == 0)
		return (0);
	final_free(data);
	free(data);
	return (0);
}
