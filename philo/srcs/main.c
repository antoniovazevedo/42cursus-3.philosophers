/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:25:29 by aazevedo          #+#    #+#             */
/*   Updated: 2022/06/11 13:35:09 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	free_data(t_params *params, t_fork **forks)
{
	if (forks)
		free_forks(forks, params->philo_count);
	free(params);
}

static int	error(t_params *params, t_fork **forks)
{
	printf("Error\n");
	free_data(params, forks);
	return (1);
}

long long	get_time_ms(long long start_time)
{
	struct timeval	*time;

	time = (struct timeval *)malloc(sizeof(struct timeval));
	gettimeofday(time, NULL);
	return ((time->tv_sec * 1000 + time->tv_usec / 1000) - start_time);
}

int	main(int argc, char **argv)
{
	t_params	*params;
	t_fork		**forks;

	if (argc < 5 || argc > 6)
	{
		printf("Error\nInvalid arguments.\n");
		return (1);
	}
	params = fill_input_from_args(argc, argv);
	if (!params)
		return (1);
	params->active = 1;
	params->start_time = get_time_ms(0);
	params->dead_philo_count = 0;
	if (pthread_mutex_init(&params->mutex, NULL) != 0)
		return (1);
	forks = create_forks(params->philo_count);
	if (!forks)
		return (error(params, forks));
	if (create_threads(params, forks) < params->philo_count)
		return (error(params, forks));
	free_data(params, forks);
	return (0);
}
