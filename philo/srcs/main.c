/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:25:29 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/23 23:13:16 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

#include <sys/time.h>
#include <unistd.h>

void	debug_params(t_params *params)
{
	printf("philo_count =\t %d\n", params->philo_count);
	printf("time_to_die =\t %d\n", params->time_to_die);
	printf("time_to_eat =\t %d\n", params->time_to_eat);
	printf("time_to_sleep =\t %d\n", params->time_to_sleep);
	if (params->number_of_times_each_philosopher_must_eat)
		printf("number_of_times_each_philosopher_must_eat =\t %d\n", params->number_of_times_each_philosopher_must_eat);
}

void	debug_philo(t_philo *philo)
{
	printf("initialize_philo (%d)\n", philo->nb);

	if (philo->right_fork)
		printf("forks: L %d\t\t R %d\n\n",
		philo->left_fork->nb, philo->right_fork->nb);
	else
		printf("forks: L %d\t\t R X\n\n", philo->left_fork->nb);
}

void	free_forks(t_fork **list, int count)
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

void	free_threads(pthread_t **list, int count)
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

t_fork	**create_forks(int count)
{
	t_fork	**forks;
	t_fork	*fork;
	int		i;

	forks = (t_fork **)malloc(sizeof(t_fork *) * count);
	i = 0;
	while (i < count)
	{
		fork = (t_fork *)malloc(sizeof(t_fork));
		if (!fork || pthread_mutex_init(&fork->mutex, NULL) != 0)
		{
			free_forks(forks, i);
			return (NULL);
		}
		fork->nb = i;
		fork->is_taken = 0;
		forks[i] = fork;
		i++;
	}
	return (forks);
}

void	print_state_message(int nb, char *state)
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
void	*thread_main(void *ptr)
{
	t_main			*data;

	data = ptr;
	sleep(1);
	print_state_message(data->philo->nb, "is initialized");
	return (NULL);
}

pthread_t	*initialize_philo(t_params *params, int nb, t_fork **forks)
{
	t_main		*main;
	t_philo		*philo;
	pthread_t	*thread;

	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->nb = nb;
	philo->state = thinking;
	philo->left_fork = forks[nb];
	philo->right_fork = forks[0];
	if (params->philo_count < 2)
		philo->right_fork = NULL;
	else if (nb + 1 < params->philo_count)
		philo->right_fork = forks[nb + 1];
	// if (pthread_mutex_init(&philo->mutex, NULL) != 0)
		return (NULL);
	debug_philo(philo);
	main = (t_main *)malloc(sizeof(t_main));
	main->params = params;
	main->philo = philo;
	thread = (pthread_t *)malloc(sizeof(pthread_t));
	pthread_create(thread, NULL, &thread_main, main);
	return (thread);
}

int	create_threads(t_params *params, t_fork **forks)
{
	int			philo_i;
	pthread_t	**threads;

	philo_i = 0;
	threads = (pthread_t **)malloc(sizeof(pthread_t) * params->philo_count);
	while (philo_i < params->philo_count)
	{
		threads[philo_i] = initialize_philo(params, philo_i, forks);
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
	if (params->philo_count < 1)
	{
		printf("Error\nNumber of philosophers must be greater than 0.\n");
		free(params);
		return (1);
	}
	debug_params(params);
	forks = create_forks(params->philo_count);
	if (!forks)
	{
		printf("Error\n");
		free(params);
		return (1);
	}
	if (create_threads(params, forks) < params->philo_count)
	{
		printf("Error\n");
		free(params);
		free_forks(forks, params->philo_count);
		return (1);
	}
	free(params);
	free_forks(forks, params->philo_count);
	return (0);
}
