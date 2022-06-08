/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:15:27 by aazevedo          #+#    #+#             */
/*   Updated: 2022/06/08 23:11:27 by aazevedo         ###   ########.fr       */
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
	int	fork1_taken;
	int	fork2_taken;
	int	ret;

	fork1_taken = 1;
	fork2_taken = 1;
	ret = 0;
	if (pthread_mutex_lock(&fork1->mutex) == 0
		&& pthread_mutex_lock(&fork2->mutex) == 0)
	{
		fork1_taken = fork1->is_taken;
		fork2_taken = fork2->is_taken;
		if (!fork1_taken && !fork2_taken)
		{
			// printf("forks %d and %d taken\n", fork1->nb, fork2->nb);

			fork1->is_taken = 1;
			fork2->is_taken = 1;
			ret = 1;
		}
		pthread_mutex_unlock(&fork1->mutex);
		pthread_mutex_unlock(&fork2->mutex);
	}
	return (ret);
}

void	drop_forks(t_fork *fork1, t_fork *fork2)
{
	pthread_mutex_lock(&fork1->mutex);
	pthread_mutex_lock(&fork2->mutex);
	fork1->is_taken = 0;
	fork2->is_taken = 0;
	// printf("forks %d and %d dropped\n", fork1->nb, fork2->nb);
	pthread_mutex_unlock(&fork1->mutex);
	pthread_mutex_unlock(&fork2->mutex);
}
