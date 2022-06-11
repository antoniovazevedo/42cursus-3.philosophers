/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:47:15 by aazevedo          #+#    #+#             */
/*   Updated: 2022/06/11 13:00:10 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_dead_count(t_params *params)
{
	int	count;

	count = 0;
	if (pthread_mutex_lock(&params->mutex) == 0)
	{
		count = params->dead_philo_count;
		pthread_mutex_unlock(&params->mutex);
	}
	return (count);
}

int	philo_is_dead(t_params *params, t_philo *philo)
{
	if (get_time_ms(0) - philo->last_meal_at >= params->time_to_die)
	{
		usleep(30 * philo->nb);
		if (philo_dead_count(params) > 0)
			return (1);
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

int	philo_has_eaten_enough(t_params *params, t_philo *philo)
{
	if (!params->min_meal_count)
		return (0);
	return (philo->meal_count == params->min_meal_count);
}
