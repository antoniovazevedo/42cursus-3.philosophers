/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:15:27 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/23 23:30:33 by aazevedo         ###   ########.fr       */
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
