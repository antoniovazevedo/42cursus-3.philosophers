/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:25:29 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/23 20:26:07 by aazevedo         ###   ########.fr       */
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

	t_philo	*philo1;
	philo1 = (t_philo *)malloc(sizeof(t_philo));
	philo1->nb = 2;
	philo1->state = eating;

	t_fork	*fork1;
	fork1 = (t_fork *)malloc(sizeof(t_fork));
	fork1->nb = 1;
	fork1->is_taken = 0;

	philo1->left_fork = fork1;
	philo1->right_fork = fork1;

	printf("\nphilo1\t\tnb: %d\tstate: %d\n", philo1->nb, philo1->state);
	printf("\nleft fork\tnb: %d\tis_taken: %d\n", philo1->left_fork->nb, philo1->left_fork->is_taken);

	philo1->left_fork->is_taken = 1;

	printf("\nleft fork\tnb: %d\tis_taken: %d\n", philo1->left_fork->nb, philo1->left_fork->is_taken);

	free(main);
	free(philo1);
	free(fork1);
	return (0);
}
