/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:47:15 by aazevedo          #+#    #+#             */
/*   Updated: 2022/06/11 18:50:29 by aazevedo         ###   ########.fr       */
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
		print_state_message_died(philo->nb + 1, params);
		if (pthread_mutex_lock(&params->mutex) == 0)
		{
			params->dead_philo_count++;
			pthread_mutex_unlock(&params->mutex);
		}
		return (1);
	}
	return (0);
}

int	everyone_has_eaten_enough(t_params *params)
{
	int	i;
	int	*meal_count;

	if (!params->min_meal_count)
		return (0);
	i = 0;
	if (pthread_mutex_lock(&params->mutex) == 0)
	{
		meal_count = params->philo_meal_count;
		pthread_mutex_unlock(&params->mutex);
		while (i < params->philo_count)
		{
			if (meal_count[i] < params->min_meal_count)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	record_meal(t_params *params, int philo_nb)
{
	if (pthread_mutex_lock(&params->mutex) == 0)
	{
		params->philo_meal_count[philo_nb]++;
		pthread_mutex_unlock(&params->mutex);
	}
}
