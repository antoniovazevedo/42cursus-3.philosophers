/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:25:29 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/23 20:44:45 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	debug_params(t_params *params)
{
	printf("philo_count =\t %d\n", params->philo_count);
	printf("time_to_die =\t %d\n", params->time_to_die);
	printf("time_to_eat =\t %d\n", params->time_to_eat);
	printf("time_to_sleep =\t %d\n", params->time_to_sleep);
	if (params->number_of_times_each_philosopher_must_eat)
		printf("number_of_times_each_philosopher_must_eat =\t %d\n", params->number_of_times_each_philosopher_must_eat);
}

int	main(int argc, char **argv)
{
	t_params	*params;

	(void) argv;

	if (argc < 5 || argc > 6)
	{
		printf("Error\nInvalid arguments.\n");
		return (1);
	}
	params = fill_input_from_args(argc, argv);
	if (params->philo_count < 1)
	{
		printf("Error\nNumber of philosophers must be greater than 0.\n");
		free(params);
		return (1);
	}
	debug_params(params);

	// Create fork struct for each fork (same as philosopher count)

	// for each philo:
		// create philo struct 
		// start thread


	free(params);
	return (0);
}
