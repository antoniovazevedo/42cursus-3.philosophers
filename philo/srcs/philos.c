/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:27:30 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/23 23:31:24 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	debug_philo(t_philo *philo)
{
	printf("initialize_philo (%d)\n", philo->nb);
	if (philo->right_fork)
		printf("forks: L %d\t\t R %d\n\n",
			philo->left_fork->nb, philo->right_fork->nb);
	else
		printf("forks: L %d\t\t R X\n\n", philo->left_fork->nb);
}

pthread_t	*initialize_philo_thread(t_params *params, int nb, t_fork **forks)
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
	if (pthread_mutex_init(&philo->mutex, NULL) != 0)
		return (NULL);
	debug_philo(philo);
	main = (t_main *)malloc(sizeof(t_main));
	main->params = params;
	main->philo = philo;
	thread = (pthread_t *)malloc(sizeof(pthread_t));
	pthread_create(thread, NULL, &main_philo_thread, main);
	return (thread);
}
