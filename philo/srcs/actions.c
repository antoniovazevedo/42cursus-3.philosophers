/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:47:15 by aazevedo          #+#    #+#             */
/*   Updated: 2022/06/11 13:00:19 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_eat_do(long long start_time, t_params *params, t_philo *philo)
{
	while (get_time_ms(start_time) < params->time_to_eat)
	{
		if (philo_is_dead(params, philo) || philo_dead_count(params) > 0)
			return (0);
	}
	return (1);
}

static int	philo_eat(t_params *params, t_philo *philo)
{
	if (philo->nb % 2 == 0)
		usleep(10);
	if (!philo->left_fork || !philo->right_fork)
		return (0);
	else if (philo_is_dead(params, philo) || philo_dead_count(params) > 0
		|| philo_has_eaten_enough(params, philo))
		return (1);
	if (pick_up_forks(philo->left_fork, philo->right_fork))
	{
		usleep(1000);
		print_state_message(philo->nb + 1, "has taken a fork", params);
		print_state_message(philo->nb + 1, "has taken a fork", params);
		update_philo_state(params, philo, eating);
		philo->last_meal_at = get_time_ms(0);
		if (!philo_eat_do(philo->last_meal_at, params, philo))
			return (1);
		drop_forks(philo->left_fork, philo->right_fork);
		philo->meal_count++;
		return (1);
	}
	return (0);
}

static void	philo_sleep(t_params *params, t_philo *philo)
{
	long long	start_time;

	update_philo_state(params, philo, sleeping);
	if (philo_dead_count(params) > 0 || philo_has_eaten_enough(params, philo))
		return ;
	start_time = get_time_ms(0);
	while (get_time_ms(start_time) < params->time_to_sleep)
	{
		if (philo_is_dead(params, philo) || philo_dead_count(params) > 0)
			return ;
	}
	philo_think(params, philo);
}

void	philo_think(t_params *params, t_philo *philo)
{
	if (philo_dead_count(params) > 0 || philo_has_eaten_enough(params, philo))
		return ;
	update_philo_state(params, philo, thinking);
	while (!philo_eat(params, philo))
	{
		if (philo_is_dead(params, philo) || philo_dead_count(params) > 0)
			return ;
	}
	philo_sleep(params, philo);
}
