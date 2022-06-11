/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:27:30 by aazevedo          #+#    #+#             */
/*   Updated: 2022/06/11 13:03:53 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*main_philo_thread(void *ptr)
{
	t_main	*data;

	data = ptr;
	philo_think(data->params, data->philo);
	return (NULL);
}

void	print_state_message(int nb, char *state, t_params *params)
{
	usleep(10);
	if (philo_dead_count(params) > 0)
		return ;
	printf("%lld %d %s\n", get_time_ms(params->start_time), nb, state);
}

pthread_t	*initialize_philo_thread(t_params *params, int nb, t_fork **forks)
{
	t_main		*main;
	t_philo		*philo;
	pthread_t	*thread;

	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->nb = nb;
	philo->last_meal_at = params->start_time;
	philo->meal_count = 0;
	philo->left_fork = forks[nb];
	philo->right_fork = forks[0];
	if (params->philo_count < 2)
		philo->right_fork = NULL;
	else if (nb + 1 < params->philo_count)
		philo->right_fork = forks[nb + 1];
	main = (t_main *)malloc(sizeof(t_main));
	main->params = params;
	main->philo = philo;
	thread = (pthread_t *)malloc(sizeof(pthread_t));
	pthread_create(thread, NULL, &main_philo_thread, main);
	return (thread);
}

void	update_philo_state(t_params *params, t_philo *philo,
			enum e_philo_state state)
{
	philo->state = state;
	if (state == thinking && philo->meal_count > 0)
		print_state_message(philo->nb + 1, "is thinking", params);
	else if (state == eating)
		print_state_message(philo->nb + 1, "is eating", params);
	else if (state == sleeping)
		print_state_message(philo->nb + 1, "is sleeping", params);
}
