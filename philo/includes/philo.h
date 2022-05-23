/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:21:11 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/23 20:40:16 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_params {
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_params;

typedef struct s_fork
{
	int				nb;
	int				is_taken;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int 			nb;
	enum e_philo_state
	{
		thinking = 0,
		eating = 1,
		sleeping = 2
	} state;
	t_fork			*left_fork;
	t_fork			*right_fork;
}	t_philo;

typedef struct s_main {
	t_params	*params;
	t_philo		*philo;
}	t_main;

t_params	*fill_input_from_args(int argc, char **args);

#endif