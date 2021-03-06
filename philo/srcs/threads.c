/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:16:09 by aazevedo          #+#    #+#             */
/*   Updated: 2022/06/11 13:34:12 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	free_threads(pthread_t **list, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (count);
}

int	create_threads(t_params *params, t_fork **forks)
{
	int			philo_i;
	pthread_t	**threads;

	philo_i = 0;
	threads = (pthread_t **)malloc(sizeof(pthread_t) * params->philo_count);
	while (philo_i < params->philo_count)
	{
		threads[philo_i] = initialize_philo_thread(params, philo_i, forks);
		if (!threads[philo_i])
			return (free_threads(threads, philo_i));
		philo_i++;
	}
	philo_i = 0;
	while (philo_i < params->philo_count)
	{
		if (pthread_join(*(threads[philo_i++]), NULL) != 0)
		{
			printf("Error when terminating thread %d\n", philo_i);
			return (philo_i);
		}
	}
	free_threads(threads, params->philo_count);
	return (params->philo_count);
}
