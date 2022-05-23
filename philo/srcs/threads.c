/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:16:09 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/23 23:29:50 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

#include <unistd.h>

static void	free_threads(pthread_t **list, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(list[i]);
		i++;
	}
	free(list);
}

static void	print_state_message(int nb, char *state)
{
	struct timeval	*time;

	time = (struct timeval *)malloc(sizeof(struct timeval));
	if (!time)
		return ;
	gettimeofday(time, NULL);
	printf("%d %d %s\n", time->tv_usec, nb, state);
	free(time);
}

// pthread_mutex_lock(&data->philo->mutex);
void	*main_philo_thread(void *ptr)
{
	t_main	*data;

	data = ptr;
	sleep(1);
	print_state_message(data->philo->nb, "is initialized");
	return (NULL);
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
		{
			free_threads(threads, philo_i);
			return (philo_i);
		}
		philo_i++;
	}
	philo_i = 0;
	while (philo_i < params->philo_count)
		pthread_join(*(threads[philo_i++]), NULL);
	return (params->philo_count);
}
