/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:47:15 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/24 01:21:23 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_is_dead(t_params *params, t_philo *philo)
{
	if (get_time_ms() - philo->last_meal_at >= params->time_to_die)
	{
		print_state_message(philo->nb + 1, "died");
		params->dead_philo_count++;
		return (1);
	}
	return (0);
}

int	philo_eat(t_params *params, t_philo *philo)
{
	if (!philo->left_fork || !philo->right_fork)
		return (0);
	else if (philo->left_fork->is_taken || philo->right_fork->is_taken)
		return (0);
	else if (params->dead_philo_count > 0 || philo_is_dead(params, philo))
		return (1);
	else if (params->min_meal_count > 0
		&& philo->meal_count == params->min_meal_count)
		return (1);
	if (pick_up_forks(philo->left_fork, philo->right_fork))
	{
		update_philo_state(philo, eating);
		pthread_mutex_lock(&philo->mutex);
		philo->last_meal_at = get_time_ms();
		pthread_mutex_unlock(&philo->mutex);
		usleep(params->time_to_eat * 1000);
		drop_forks(philo->left_fork, philo->right_fork);
		pthread_mutex_lock(&philo->mutex);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	return (0);
}

void	philo_think(t_params *params, t_philo *philo)
{
	if (params->dead_philo_count > 0
		|| (params->min_meal_count > 0
			&& philo->meal_count == params->min_meal_count))
		return ;
	update_philo_state(philo, thinking);
	while (!philo_eat(params, philo))
	{
		usleep(50000);
		if (params->dead_philo_count > 0 || philo_is_dead(params, philo))
			return ;
	}
	philo_sleep(params, philo);
}

void	philo_sleep(t_params *params, t_philo *philo)
{
	if (params->dead_philo_count > 0
		|| (params->min_meal_count > 0
			&& philo->meal_count == params->min_meal_count))
		return ;
	update_philo_state(philo, sleeping);
	usleep(params->time_to_sleep * 1000);
	philo_think(params, philo);
}
