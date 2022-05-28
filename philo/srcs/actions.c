/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:47:15 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/28 23:08:29 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_is_dead(t_params *params, t_philo *philo)
{
	if (get_time_ms(0) - philo->last_meal_at >= params->time_to_die)
	{
		print_state_message(philo->nb + 1, "died", params);
		if (pthread_mutex_lock(&params->mutex) == 0)
		{
			params->dead_philo_count++;
			pthread_mutex_unlock(&params->mutex);
		}
		return (1);
	}
	return (0);
}

static int	philo_has_eaten_enough(t_params *params, t_philo *philo)
{
	if (!params->min_meal_count)
		return (0);
	return (philo->meal_count == params->min_meal_count);
}

int	philo_eat(t_params *params, t_philo *philo)
{
	if (!philo->left_fork || !philo->right_fork)
		return (0);
	else if (philo->left_fork->is_taken || philo->right_fork->is_taken)
		return (0);
	else if (philo_dead_count(params) > 0 || philo_is_dead(params, philo)
		|| philo_has_eaten_enough(params, philo))
		return (1);
	if (pick_up_forks(philo->left_fork, philo->right_fork))
	{
		print_state_message(philo->nb + 1, "has taken a fork", params);
		print_state_message(philo->nb + 1, "has taken a fork", params);
		update_philo_state(params, philo, eating);
		pthread_mutex_lock(&philo->mutex);
		philo->last_meal_at = get_time_ms(0);
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
	if (philo_dead_count(params) > 0 || philo_has_eaten_enough(params, philo))
		return ;
	update_philo_state(params, philo, thinking);
	while (!philo_eat(params, philo))
	{
		usleep(50000);
		if (philo_dead_count(params) > 0 || philo_is_dead(params, philo))
			return ;
	}
	philo_sleep(params, philo);
}

void	philo_sleep(t_params *params, t_philo *philo)
{
	if (philo_dead_count(params) > 0 || philo_has_eaten_enough(params, philo))
		return ;
	update_philo_state(params, philo, sleeping);
	usleep(params->time_to_sleep * 1000);
	philo_think(params, philo);
}
