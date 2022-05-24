/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:15:27 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/24 01:10:56 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	pick_up_forks(t_fork *fork1, t_fork *fork2)
{
	if (pthread_mutex_lock(&fork1->mutex) == 0
		&& pthread_mutex_lock(&fork2->mutex) == 0)
	{
		fork1->is_taken = 1;
		fork2->is_taken = 1;
		pthread_mutex_unlock(&fork1->mutex);
		pthread_mutex_unlock(&fork2->mutex);
		return (1);
	}
	return (0);
}

void	drop_forks(t_fork *fork1, t_fork *fork2)
{
	pthread_mutex_lock(&fork1->mutex);
	pthread_mutex_lock(&fork2->mutex);
	fork1->is_taken = 0;
	fork2->is_taken = 0;
	pthread_mutex_unlock(&fork1->mutex);
	pthread_mutex_unlock(&fork2->mutex);
}
