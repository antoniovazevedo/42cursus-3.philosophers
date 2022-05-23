/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:25:29 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/23 20:08:43 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	debug_main(t_main *main)
{
	printf("philo_count =\t %d\n", main->philo_count);
	printf("time_to_die =\t %d\n", main->time_to_die);
	printf("time_to_eat =\t %d\n", main->time_to_eat);
	printf("time_to_sleep =\t %d\n", main->time_to_sleep);
	if (main->number_of_times_each_philosopher_must_eat)
		printf("number_of_times_each_philosopher_must_eat =\t %d\n", main->number_of_times_each_philosopher_must_eat);
}

int	main(int argc, char **argv)
{
	t_main	*main;

	(void) argv;

	if (argc < 5 || argc > 6)
	{
		printf("Error\nInvalid arguments.\n");
		return (1);
	}
	main = fill_input_from_args(argc, argv);
	if (main->philo_count < 1)
	{
		printf("Error\nNumber of philosophers must be greater than 0.\n");
		free(main);
		return (1);
	}
	debug_main(main);

	free(main);
	return (0);
}
