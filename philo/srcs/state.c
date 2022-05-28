/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:47:15 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/28 23:09:48 by aazevedo         ###   ########.fr       */
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
